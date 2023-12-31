#include "m68k.h"
#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "compact/c_compact.hpp"


#define MAX_ROM 0xfff                           /* Memory size for rom */
#define MAX_RAM 0xffffff                            /* Memory size for ram */
#define MAX_MEM (MAX_RAM)               /* ROM and RAM sizes */
#define MEMAVAIL_ADDRESS 0x4100000C              /* Memory availble address */
#define MEMAVAIL_VALUE_ADDRESS 0x41000010   /* Amount of memory configured */
#define PLANEMASK_ADDRESS 0x410000B8          /* Plane mask address */
#define PLANEMASK_VALUE_ADDRESS 0x410000C0    /* Plane mask value */
#define BOOTARG_ADDRESS 0x410000D4            /* Boot argument address */
#define BOOTARG_START 0x42000000                /* Boot argument start address */
#define BOOTARG_END (BOOTARG_START + 64 - 1)  /* Boot argument end address */

#define WRITE_32(BASE, ADDR, VAL) do {                   \
    (BASE)[ADDR] = ((VAL) >> 24) & 0xff;                 \
    (BASE)[(ADDR) + 1] = ((VAL) >> 16) & 0xff;           \
    (BASE)[(ADDR) + 2] = ((VAL) >> 8) & 0xff;            \
    (BASE)[(ADDR) + 3] = (VAL) & 0xff;                   \
} while(0)


/* Prototypes DO WE NEED THESE HERE? apg*/
void exit_error(char* fmt, ...);
unsigned int  m68k_read_memory_8(unsigned int address);
unsigned int  m68k_read_memory_16(unsigned int address);
unsigned int  m68k_read_memory_32(unsigned int address);
void m68k_write_memory_8(unsigned int address, unsigned int value);
void m68k_write_memory_16(unsigned int address, unsigned int value);
void m68k_write_memory_32(unsigned int address, unsigned int value);
void data_bus_recorder(const char *string, unsigned int address, unsigned int size);

/* initiallize memory array to 0 */
unsigned char g_mem[MAX_MEM+1] = {0};                 /* Memory in one array */
unsigned char bootarg[64] = {0};                            /* Boot argument */


/* struct definition */
struct section {
    const char* name;
    unsigned int address;
    unsigned int size;
};

/* PIOs */
unsigned int OBIO_PIO0A	= 0x00;	/* PIO-0 port A */
unsigned int OBIO_PIO0B	= 0x00;	/* PIO-0 port B */
unsigned int OBIO_PIO0C	= 0x00;	/* PIO-0 port C*/
unsigned int OBIO_PIO0	= 0x00;	/* PIO-0 control */

/* track instruction execution */
void instruction_hook(unsigned int pc)
{
    printf("Now executing PC vvv: %08x\n", pc);
    if(pc == 70294)
    {
      printf("Starting pmap_kenter_pa()\n");
    }
   // unsigned int r = m68k_get_reg(NULL, M68K_REG_SRP);
    // printf("Current value of D2: %08x\n",r);
}

/*portA data 51000000 
portA command 51000002
portB data 51000001
portB command 51000006 */

/*strings used to store serial IO port writes*/
char *port_A_data, *port_B_data, *port_A_command, *port_B_command;
size_t port_A_data_n, port_A_data_p;
size_t port_B_data_n, port_B_data_p;

size_t port_A_data_size, port_A_command_size, port_B_data_size, port_B_command_size;
#define BUF_STEP_SIZE 100

/*used for appending commands and data to serial IO ports*/
void append_to_string(char **dest, const char *src, size_t *dest_size) {
   size_t dest_len = strlen(*dest);
   size_t src_len = strlen(src);
   if(dest_len + src_len + 1 > *dest_size)
   {
      char* temp = (char*)malloc(*dest_size + BUF_STEP_SIZE);
      *dest_size += BUF_STEP_SIZE;
      strcpy(temp, *dest);
      strcat(temp, src);
      free(*dest);
      *dest = temp;
   }
   else
   {
      strcat(*dest, src);
   }
}

/* read serial IO port define */
unsigned char serial_IO_read(unsigned int address){
    return 0xff; 
}


/* write serial IO port define */
void serial_IO_write(unsigned int address, unsigned char data){
    char buffer[10];
    sprintf(buffer, "%c", data);
    switch (address){
        case 0x51000000:
            port_A_data_n++;
            append_to_string(&port_A_data, buffer, &port_A_data_size);
            if(data == '\n')
            {
               printf("portA::");
               puts(port_A_data+port_A_data_p);
               port_A_data_p = port_A_data_n;
            }
            return;
        case 0x51000001:
            port_B_data_n++;
            append_to_string(&port_B_data, buffer, &port_B_data_size);
            if(data == '\n')
            {
               printf("portB::");
               puts(port_B_data+port_B_data_p);
               port_B_data_p = port_A_data_n;
            }
            return;
        case 0x51000002:
            append_to_string(&port_A_command, buffer, &port_A_command_size);
            return;
        case 0x51000006:
            append_to_string(&port_B_command, buffer, &port_B_command_size);
            return;
        default:
            exit_error("temp error msg%08x\n", address);
    }
}


/* check if it is requesting serial IO port */
int serial_IO_check(unsigned int address) {
    switch (address) {
        case 0x51000000:
        case 0x51000001:
        case 0x51000002:
        case 0x51000006:
            return 1;
        default:
            return 0;
    }
}

/* return PIO port define */
unsigned int obio_pio_port(unsigned int address) {
    switch (address) {
        case 0x49000000:
            printf("Read OBIO_PIO0A\n");
            return OBIO_PIO0A;
        case 0x49000001:
            printf("Read OBIO_PIO0B\n");
            return OBIO_PIO0B;
        case 0x49000002:
            printf("Read OBIO_PIO0C\n");
            return OBIO_PIO0C;
        case 0x49000003:
            printf("Read OBIO_PIO0 Control\n");
            return OBIO_PIO0;
        default:
            exit_error("Invalid OBIO PIO port address %08x\n", address);
            return 0; //what should we return here?
    }
}


/* write PIO port define */
void obio_pio_port_write(unsigned int address, unsigned int value) {
    switch (address) {
        case 0x49000000:
            printf("Write OBIO_PIO0A\n");
            OBIO_PIO0A = value;
            break;
        case 0x49000001:
            printf("Write OBIO_PIO0B\n");
            OBIO_PIO0B = value;
            break;
        case 0x49000002:
            printf("Write OBIO_PIO0C\n");
            OBIO_PIO0C = value;
            break;
        case 0x49000003:
            printf("Write OBIO_PIO0 Control\n");
            OBIO_PIO0 = value;
            break;
        default:
            exit_error("Invalid OBIO PIO port address %08x\n", address);
    }
}

/* check if it is requesting OBIO PIO port */
int obio_pio_port_check(unsigned int address) {
    switch (address) {
        case 0x49000000:
        case 0x49000001:
        case 0x49000002:
        case 0x49000003:
            return 1;
        default:
            return 0;
    }
}

/* The sections to load */
struct section sections[] = {
        {"text", 0x0000c000, 0x001f5bfc},
        {"rodata", 0x00201c00, 0x0002f885},
        {"link_set_sysctl_funcs", 0x00231488, 0x000000c8},
        {"link_set_modules", 0x00231550, 0x00000108},
        {"link_set_domains", 0x00231658, 0x00000020},
        {"link_set_evcnts", 0x00231678, 0x00000048},
        {"link_set_dkwedge_methods", 0x002316c0, 0x00000004},
        {"link_set_prop_linkpools", 0x002316c4, 0x00000020},
        {"data", 0x00231740, 0x00016b8c},
        {"bss", 0x00248300, 0x00018858},
};

/* Load a section from a file into memory */
void load_section(const struct section* sec) {
    char filepath[128];
    snprintf(filepath, sizeof(filepath), "./bins/%s.bin", sec->name);

    FILE *fhandle = fopen(filepath, "rb");
    if (!fhandle) {
        exit_error("Unable to open %s", filepath);
    }

    fread(&g_mem[sec->address], 1, sec->size, fhandle);
    fclose(fhandle);
}

int main(int argc, char* argv[]) {
   port_A_data = (char *)malloc(BUF_STEP_SIZE);
   port_A_command = (char *)malloc(BUF_STEP_SIZE);
   port_B_data = (char *)malloc(BUF_STEP_SIZE);
   port_B_command = (char *)malloc(BUF_STEP_SIZE);
   
   port_A_data_p = port_A_data_n = 0;
   port_B_data_p = port_A_data_n = 0;
   
   port_A_data_size =  port_A_command_size = port_B_data_size = port_B_command_size = BUF_STEP_SIZE;
      
    unsigned int text_section_address = 0x0000c000; // Example address

    // Convert the address to bytes and store it at memory[4] to memory[7]
    WRITE_32(g_mem, 4, text_section_address);
    for (unsigned long i = 0; i < sizeof(sections) / sizeof(sections[0]); i++) {
        load_section(&sections[i]);
    }
    m68k_init();
    m68k_set_cpu_type(M68K_CPU_TYPE_68030);
    m68k_pulse_reset();

    while(TRUE){
        m68k_execute(100000);
    }

}
