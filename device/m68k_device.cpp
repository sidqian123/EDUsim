#include "m68k_device.hpp"

m68k_device::m68k_device() {
    // Constructor implementation
   port_A_data = (char *)malloc(BUF_STEP_SIZE);
   port_A_command = (char *)malloc(BUF_STEP_SIZE);
   port_B_data = (char *)malloc(BUF_STEP_SIZE);
   port_B_command = (char *)malloc(BUF_STEP_SIZE);
   
   port_A_data_p = port_A_data_n = 0;
   port_B_data_p = port_A_data_n = 0;
   
   port_A_data_size =  port_A_command_size = port_B_data_size = port_B_command_size = BUF_STEP_SIZE;

   /* PIOs */
    OBIO_PIO0A	= 0x00;	/* PIO-0 port A */
    OBIO_PIO0B	= 0x00;	/* PIO-0 port B */
    OBIO_PIO0C	= 0x00;	/* PIO-0 port C*/
    OBIO_PIO0	= 0x00;	/* PIO-0 control */
}

m68k_device::~m68k_device() {
    // Destructor implementation
   free(port_A_data);
   free(port_A_command);
   free(port_B_data);
   free(port_B_command);
}

void m68k_device::exit_error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

void m68k_device::write(unsigned int data,unsigned int address) {
    // Implement the write method specific to m68k_device
    if(obio_pio_port_check(address)){
        obio_pio_port_write(address,data);
    }
    else if(serial_IO_check(address)){
        serial_IO_write(address,data);
    }
    else{
        exit_error("Invalid device port address %08x\n", address);
    }
}

unsigned int m68k_device::read(unsigned int address) {
    if(obio_pio_port_check(address)){
        return obio_pio_port(address);
    }
    else if(serial_IO_check(address)){
        return serial_IO_read(address);
    }
    else{
        exit_error("Invalid device port address %08x\n", address);
    }
}



/* read serial IO port define */
unsigned char m68k_device::serial_IO_read(unsigned int address){
    return 0xff; 
}


/* write serial IO port define */
void m68k_device::serial_IO_write(unsigned int address, unsigned char data){
    char buffer[10];
    printf(buffer, "%c", data);
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
               puts(port_B_data + port_B_data_p);
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
int m68k_device::serial_IO_check(unsigned int address) {
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
unsigned int m68k_device::obio_pio_port(unsigned int address) {
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
void m68k_device::obio_pio_port_write(unsigned int address, unsigned int value) {
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
int m68k_device::obio_pio_port_check(unsigned int address) {
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

/*used for appending commands and data to serial IO ports*/
void m68k_device::append_to_string(char **dest, const char *src, size_t *dest_size) {
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