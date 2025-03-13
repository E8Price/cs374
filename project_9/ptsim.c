#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MEM_SIZE 16384  // MUST equal PAGE_SIZE * PAGE_COUNT
#define PAGE_SIZE 256   // MUST equal 2^PAGE_SHIFT
#define PAGE_COUNT 64
#define PAGE_SHIFT 8    // Shift page number this much

#define PTP_OFFSET 64   // Where process page table pointers start in zero page

// Simulated RAM
unsigned char mem[MEM_SIZE];

//
// Convert a page,offset into an address
//
int get_address(int page, int offset)
{
    return (page << PAGE_SHIFT) | offset;
}

//
// Initialize RAM
//
void initialize_mem(void)
{
    memset(mem, 0, MEM_SIZE);
    mem[get_address(0, 0)] = 1;  // Zero page is always reserved
}

//
// Get the page table page for a given process
//
unsigned char get_page_table(int proc_num)
{
    int ptp_addr = get_address(0, PTP_OFFSET + proc_num);
    return mem[ptp_addr];
}

//
// Find a free physical page (return its page number), or -1 if no free page.
//
int find_free_page(void)
{
    for (int page_num = 1; page_num < PAGE_COUNT; page_num++) {
        int free_map_addr = get_address(0, page_num);
        if (mem[free_map_addr] == 0) { 
            mem[free_map_addr] = 1;
            return page_num;
        }
    }
    return -1; 
}

//
// Allocate pages for a new process, and set up its page table.
//
void new_process(int proc_num, int page_count)
{
    int page_table_page = find_free_page();
    if (page_table_page < 0) {
        printf("OOM: proc %d: page table\n", proc_num);
        return; 
    }

    int ptp_addr = get_address(0, PTP_OFFSET + proc_num);
    mem[ptp_addr] = (unsigned char)page_table_page;

    printf("Process %d allocated page table at physical page %02x\n", proc_num, page_table_page);

    for (int vp = 0; vp < page_count; vp++) {
        int phys_page = find_free_page();
        if (phys_page < 0) {
            printf("OOM: proc %d: data page\n", proc_num);
            return; 
        }

        int page_table_addr = get_address(page_table_page, vp);
        mem[page_table_addr] = (unsigned char)phys_page;

        printf("Process %d: Virtual Page %02x -> Physical Page %02x\n", proc_num, vp, phys_page);
    }
}

//
// Free pages allocated to a process and remove its page table
//
void kill_process(int proc_num)
{
    int page_table_page = get_page_table(proc_num);
    if (page_table_page == 0) {
        return;
    }

    for (int vp = 0; vp < PAGE_COUNT; vp++) {
        int page_table_addr = get_address(page_table_page, vp);
        int phys_page = mem[page_table_addr];
        if (phys_page != 0) {
            int free_map_addr = get_address(0, phys_page);
            mem[free_map_addr] = 0; 
        }
    }

    int free_map_addr = get_address(0, page_table_page);
    mem[free_map_addr] = 0;

    int ptp_addr = get_address(0, PTP_OFFSET + proc_num);
    mem[ptp_addr] = 0;
}

//
// Convert a virtual address to a physical address
//
int virtual_to_physical(int proc_num, int virtual_address)
{
    int page_table_page = get_page_table(proc_num);
    if (page_table_page == 0) {
        printf("Error: Process %d has no page table\n", proc_num);
        return -1;
    }

    int virtual_page = virtual_address >> PAGE_SHIFT;
    int offset = virtual_address & 255;

    int page_table_addr = get_address(page_table_page, virtual_page);
    int physical_page = mem[page_table_addr];

    if (physical_page == 0) {
        printf("Error: Virtual page %d is not mapped\n", virtual_page);
        return -1;
    }

    return (physical_page << PAGE_SHIFT) | offset;
}

//
// Store a value at a virtual address
//
void store_value(int proc_num, int virtual_address, int value)
{
    int physical_address = virtual_to_physical(proc_num, virtual_address);
    if (physical_address == -1) {
        printf("Segmentation fault: Invalid memory access\n");
        return;
    }

    mem[physical_address] = (unsigned char)value;
    printf("Store proc %d: %d => %d, value=%d\n", proc_num, virtual_address, physical_address, value);
}

//
// Load a value from a virtual address
//
void load_value(int proc_num, int virtual_address)
{
    int physical_address = virtual_to_physical(proc_num, virtual_address);
    if (physical_address == -1) {
        printf("Segmentation fault: Invalid memory access\n");
        return;
    }

    int value = mem[physical_address];
    printf("Load proc %d: %d => %d, value=%d\n", proc_num, virtual_address, physical_address, value);
}

//
// Print the free page map
//
void print_page_free_map(void)
{
    printf("--- PAGE FREE MAP ---\n");
    for (int i = 0; i < PAGE_COUNT; i++) {
        int addr = get_address(0, i);
        printf("%c", mem[addr] == 0 ? '.' : '#');

        if ((i + 1) % 16 == 0)
            putchar('\n');
    }
}

//
// Print the address map from virtual pages to physical
//
void print_page_table(int proc_num)
{
    printf("--- PROCESS %d PAGE TABLE ---\n", proc_num);

    int page_table = get_page_table(proc_num);

    if (page_table == 0) {
        return; 
    }

    for (int i = 0; i < PAGE_COUNT; i++) {
        int addr = get_address(page_table, i);
        int page = mem[addr];
        if (page != 0) {
            printf("%02x -> %02x\n", i, page);
        }
    }
}

//
// Main -- process command line
//
int main(int argc, char *argv[])
{
    assert(PAGE_COUNT * PAGE_SIZE == MEM_SIZE);

    if (argc == 1) {
        fprintf(stderr, "usage: ptsim commands\n");
        return 1;
    }

    initialize_mem();

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "pfm") == 0) {
            print_page_free_map();
        }
        else if (strcmp(argv[i], "ppt") == 0) {
            int proc_num = atoi(argv[++i]);
            print_page_table(proc_num);
        }
        else if (strcmp(argv[i], "np") == 0) {
            int proc_num = atoi(argv[++i]);
            int page_count = atoi(argv[++i]);
            new_process(proc_num, page_count);
        }
        else if (strcmp(argv[i], "kp") == 0) {
            int proc_num = atoi(argv[++i]);
            kill_process(proc_num);
        }
        else if (strcmp(argv[i], "sb") == 0) {
            int proc_num = atoi(argv[++i]);
            int vaddr = atoi(argv[++i]);
            int value = atoi(argv[++i]);
            store_value(proc_num, vaddr, value);
        }
        else if (strcmp(argv[i], "lb") == 0) {
            int proc_num = atoi(argv[++i]);
            int vaddr = atoi(argv[++i]);
            load_value(proc_num, vaddr);
        }
        else {
            fprintf(stderr, "Unknown command: %s\n", argv[i]);
        }
    }

    return 0;
}
