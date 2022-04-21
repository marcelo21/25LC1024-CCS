////////////////////////// INSTRUCTION SET

#define READ    0x03    // Read data from memory array beginning at selected address.
#define WRITE   0x02    // Write data to memory array beginning at selected address.
#define WREN    0x06    // Set the write enable latch (enable write operations).
#define WRDI    0x04    // Reset the write enable latch (disable write operations).
#define RDSR    0x05    // Read STATUS register.
#define WRSR    0x01    // Write STATUS register.

#define PE      0x42    // Page Erase – erase one page in memory array.
#define SE      0xD8    // Sector Erase – erase one sector in memory array.
#define CE      0xC7    // Chip Erase – erase all sectors in memory array.
#define RDID    0xAB    // Release from Deep power-down and read electronic signature.
#define DPD     0xB9    // Deep Power-Down mode.

unsigned int readEeprom( unsigned long address )
{
    unsigned int data;
    unsigned int address_3;
    unsigned int address_2;
    unsigned int address_1;    

    address_3 = ( address >> 16 ) & 0xFF;
    address_2 = ( address >> 8  ) & 0xFF;
    address_1 = ( address >> 0  ) & 0xFF;

    display_1 = 1;
    io = 1;

    eeprom = 0;
    spi.write( READ );
    spi.write( address_3 );
    spi.write( address_2 );
    spi.write( address_1 );
    data = spi.write( 0x00 );
    eeprom = 1;

    return data;
}

void writeEeprom( unsigned long address, unsigned int data )
{
    unsigned int address_3;
    unsigned int address_2;
    unsigned int address_1;  

    address_3 = ( address >> 16 ) & 0xFF;
    address_2 = ( address >> 8  ) & 0xFF;
    address_1 = ( address >> 0  ) & 0xFF;

    display_1 = 1;
    io = 1;

    eeprom = 0;
    spi.write( WREN );
    eeprom = 1;

    eeprom = 0;
    spi.write( WRITE );
    spi.write( address_3 );
    spi.write( address_2 );
    spi.write( address_1 );
    spi.write( data );
    eeprom = 1;

    delay_ms( 6 );
    //thread_sleep_for( 6 );

    eeprom = 0;
    spi.write( WRDI );
    eeprom = 1;
}