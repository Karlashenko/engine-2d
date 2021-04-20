#pragma once

void bitmap_flip_vertical(U8* p_bitmap, U32 p_width, U32 p_height, U32 p_bytes_per_pixel)
{
    U32 bytes_per_row = p_width * p_bytes_per_pixel;
    U8* bytes = p_bitmap;

    U8 temp[2048];
    for (int row = 0; row < (p_height >> 1); row++) {
        U8* row0 = bytes + row * bytes_per_row;
        U8* row1 = bytes + (p_height - row - 1) * bytes_per_row;

        U32 bytes_left = bytes_per_row;
        while (bytes_left > 0) {
            U32 bytes_copy = (bytes_left < sizeof(temp)) ? bytes_left : sizeof(temp);

            memcpy(temp, row0, bytes_copy);
            memcpy(row0, row1, bytes_copy);
            memcpy(row1, temp, bytes_copy);

            row0 += bytes_copy;
            row1 += bytes_copy;

            bytes_left -= bytes_copy;
        }
    }
}
