#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE file_handle = CreateFile("read.txt", GENERIC_READ,0,0, OPEN_EXISTING, 0, 0);

    char buffer[1024];
    DWORD bytes_read;
    DWORD bytes_write;

    ReadFile(file_handle, buffer, sizeof(buffer)-1, &bytes_read, 0);
    buffer[bytes_read]=0;
    WriteConsoleA(std_out, buffer, bytes_read, &bytes_write, 0);
    CloseHandle(file_handle);

    CONSOLE_SCREEN_BUFFER_INFO screen_info;
    GetConsoleScreenBufferInfo(std_out, &screen_info);

    COORD result_output_pos = {0, screen_info.dwCursorPosition.Y + 2};

    HANDLE std_in=GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(std_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    while(1){
        INPUT_RECORD input_record;
        ReadConsoleInput(std_in, &input_record, 1, &bytes_write);

        if(input_record.EventType == MOUSE_EVENT){
            if(input_record.Event.MouseEvent.dwButtonState & 
                RIGHTMOST_BUTTON_PRESSED){
                break;
            }

            if(input_record.Event.MouseEvent.dwButtonState &
            FROM_LEFT_1ST_BUTTON_PRESSED){
                char clicked_char;
                DWORD chars_read_count;

                ReadConsoleOutputCharacterA(
                    std_out,
                    &clicked_char,
                    1,
                    input_record.Event.MouseEvent.dwMousePosition,
                    &chars_read_count
                );

                if(clicked_char > ' '){
                    SetConsoleCursorPosition(std_out, result_output_pos);

                    printf("%c [%d, %d]", 
                    clicked_char,
                    input_record.Event.MouseEvent.dwMousePosition.Y + 1, 
                    input_record.Event.MouseEvent.dwMousePosition.X +1 );
                }
            }
        }
    }
    
    return 0;
}