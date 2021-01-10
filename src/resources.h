/*
*   resources.h
*/

#ifndef __RESOURCES
#define __RESOURCES

#include <stdlib.h>
#include <stdint.h>
#include "lib.h"

class Resource {
    private:
        uint8_t* start;
        uint8_t* end;
        uint8_t size;

        void load() {
            read(this->data, this->start, this->size);
        }
    public:
        uint8_t* data;
        Resource(uint8_t* start, uint8_t* end) {
            this->start = start;
            this->end = end;
            this->size = end - start;
            this->data = (uint8_t*)malloc(this->size);

            this->load();
        }
};

extern uint8_t* _binary_src_scrpt_remove_bat_start;
extern uint8_t* _binary_src_scrpt_remove_bat_end;
// Resource scrpt_remove = Resource(_binary_src_scrpt_remove_bat_start, _binary_src_scrpt_remove_bat_end);

#endif