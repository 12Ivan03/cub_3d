
#include "cub3d.h"

void mm_fill_rect(mlx_image_t *img, int x, int y, int w, int h, uint32_t c)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            mlx_put_pixel(img, x + xx, y + yy, c);
}

void    draw_mini_map(t_game **game)
{
    int i;
    int j;

    i = 0;
    while (i < (*game)->height)
    {
        j = 0;
        while (j < (*game)->width)
        {
            int px = j * 8;
            int py = i * 8;

            char cell = (*game)->map[i][j];
            if (cell == '1')
                mm_fill_rect((*game)->mini_map_image, px, py, 8, 8, 0x777777FF);
            else
                mm_fill_rect((*game)->mini_map_image, px, py, 8, 8, 0x101000AA);
            j++;
        }
        i++;
    }

    // put player 
    int player_mm_x = (int)(((*game)->player.position.x / (float)GRID_SIZE) * 8.0f);
    int player_mm_y = (int)(((*game)->player.position.y / (float)GRID_SIZE) * 8.0f);

    mm_fill_rect((*game)->mini_map_image, player_mm_x - 2, player_mm_y - 2, 5, 5, 0xFF0000FF);

    // put view direction
    int k;
    float angle_rad = (*game)->player.angle_alpha * M_PI / 180.0f;

    k = 0;
    while (k < 30)
    {
        int lx = player_mm_x + (int)(cosf(angle_rad) * k);
        int ly = player_mm_y - (int)(sinf(angle_rad) * k);
        if (lx >= 0 && lx < (int)(*game)->mini_map_image->width && ly >= 0 && ly < (int)(*game)->mini_map_image->height)
            mlx_put_pixel((*game)->mini_map_image, lx, ly, 0xFF0000FF);
        k++;
    }
}


// void    draw_mini_map(t_game **game)
// {
//     int i;
//     int j;

//     const int tile_size = 8;
//     int img_w = (int)(*game)->mini_map_image->width;
//     int img_h = (int)(*game)->mini_map_image->height;

//     int player_mm_x = (int)(((*game)->player.position.x / (float)GRID_SIZE) * tile_size);
//     int player_mm_y = (int)(((*game)->player.position.y / (float)GRID_SIZE) * tile_size);

//     float start_px = (float)player_mm_x - img_w / 2.0f;
//     float start_py = (float)player_mm_y - img_h / 2.0f;

//     int start_tile_x = (int)floorf(start_px / (float)tile_size);
//     int start_tile_y = (int)floorf(start_py / (float)tile_size);
//     int end_tile_x = (int)ceilf((start_px + img_w) / (float)tile_size);
//     int end_tile_y = (int)ceilf((start_py + img_h) / (float)tile_size);

//     if (start_tile_x < 0) start_tile_x = 0;
//     if (start_tile_y < 0) start_tile_y = 0;
//     if (end_tile_x > (*game)->width - 1) end_tile_x = (*game)->width - 1;
//     if (end_tile_y > (*game)->height - 1) end_tile_y = (*game)->height - 1;

//     for (int ty = start_tile_y; ty <= end_tile_y; ty++)
//     {
//         for (int tx = start_tile_x; tx <= end_tile_x; tx++)
//         {
//             int px = (int)(tx * tile_size - start_px);
//             int py = (int)(ty * tile_size - start_py);
//             if (px + tile_size < 0 || py + tile_size < 0 || px >= img_w || py >= img_h)
//                 continue;
//             char cell = (*game)->map[ty][tx];
//             if (cell == '1')
//                 mm_fill_rect((*game)->mini_map_image, px, py, tile_size, tile_size, 0x777777FF);
//         }
//     }

//     /* draw player centered in the mini-map image */
//     int center_x = img_w / 2;
//     int center_y = img_h / 2;
//     mm_fill_rect((*game)->mini_map_image, center_x - 2, center_y - 2, 5, 5, 0xFF0000FF);

//     /* direction line from center */
//     float angle_rad = (*game)->player.angle_alpha * M_PI / 180.0f;
//     for (int k = 0; k < 40; k++)
//     {
//         int lx = center_x + (int)(cosf(angle_rad) * k);
//         int ly = center_y - (int)(sinf(angle_rad) * k);
//         if (lx >= 0 && lx < img_w && ly >= 0 && ly < img_h)
//             mlx_put_pixel((*game)->mini_map_image, lx, ly, 0xFF0000FF);
//     }
// }