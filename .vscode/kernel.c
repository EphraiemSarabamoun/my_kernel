/* We'll define some basic types we need */
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

/* Video memory constants */
#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

/* Color codes for VGA text mode */
enum vga_color {
    COLOR_BLACK = 0,
    COLOR_LIGHT_GREY = 7,
    COLOR_WHITE = 15,
};

/* Function to combine character and color into a VGA entry */
uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t) c | ((uint16_t) color << 8);
}

/* Function to clear the entire screen to a blank state */
void terminal_clear() {
    volatile uint16_t* video_memory = (uint16_t*) VGA_MEMORY;
    uint8_t color = COLOR_WHITE | (COLOR_BLACK << 4);
    
    // Loop through every position on the screen and set it to a space character
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        video_memory[i] = vga_entry(' ', color);
    }
}

/* Function to write a single character at a specific position */
void terminal_putchar(int x, int y, char c, uint8_t color) {
    volatile uint16_t* video_memory = (uint16_t*) VGA_MEMORY;
    // Calculate the position in linear memory from x,y coordinates
    const int index = y * VGA_WIDTH + x;
    video_memory[index] = vga_entry(c, color);
}

/* Function to write a string at a specific position */
void terminal_writestring_at(int x, int y, const char* str, uint8_t color) {
    for (int i = 0; str[i] != '\0'; i++) {
        // Write each character of the string, advancing the x position
        terminal_putchar(x + i, y, str[i], color);
    }
}

/* The original string writing function (kept for compatibility) */
void terminal_writestring(const char* str) {
    volatile uint16_t* video_memory = (uint16_t*) VGA_MEMORY;
    uint8_t color = COLOR_WHITE | (COLOR_BLACK << 4);
    
    for (int i = 0; str[i] != '\0'; i++) {
        video_memory[i] = vga_entry(str[i], color);
    }
}

/* Our kernel's main function */
void kernel_main(void) {
    // Start with a clean screen
    terminal_clear();
    
    // Write our initial messages
    terminal_writestring_at(0, 0, "Hello from my first kernel!", COLOR_WHITE);
    terminal_writestring_at(0, 1, "Kernel is running... Watch the animation below:", COLOR_WHITE);
    
    // Create a simple animation to show the kernel is alive
    char spinner[] = {'|', '/', '-', '\\'};
    int spinner_pos = 0;
    int x = 0;
    
    // Main kernel loop - keeps our kernel running and updates the animation
    while(1) {
        // Update spinner character at current position
        terminal_putchar(x, 3, spinner[spinner_pos], COLOR_LIGHT_GREY);
        
        // Move to next spinner frame and position
        spinner_pos = (spinner_pos + 1) % 4;
        x = (x + 1) % VGA_WIDTH;
        
        // Simple delay to make the animation visible
        for(volatile int i = 0; i < 1000000; i++) { }
    }
}