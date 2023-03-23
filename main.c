#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    // Queue control
    uint8_t head;
    uint8_t tail;
    uint8_t size;
    uint8_t capacity;

    // Event data
    uint8_t *data;
    uint8_t dataSize;

    // Function
    void (*ptr_hello)(void);
    uint8_t index;
} Queue_t;

// switch(nana) {
//     case 1:
//     case 2:
// }
// void (*ptr_hello)(void)[10];

// while(nana) {
//     queue->ptr_hello[index]();
// }



Queue_t *createQueue(uint8_t capacity, uint8_t size);
bool enQueue(Queue_t *queue, uint8_t data);
bool deQueue(Queue_t *queue, uint8_t *data);
bool isQueueFull(Queue_t *queue);
bool isQueueEmpty(Queue_t *queue);
void hello(void);

void hello(void)
{
    printf("Hello world\n");
}

Queue_t *createQueue(uint8_t capacity, uint8_t size){
    Queue_t *queue = (Queue_t *) malloc(sizeof(Queue_t));

    // Init control variables
    queue->head = 0;
    queue->tail = capacity - 1;
    queue->capacity = capacity;
    queue->size = 0;

    // Allocate data space in RAM
    queue->data = malloc(size * queue->capacity);
    queue->dataSize = size;
    queue->ptr_hello = hello;
    return queue;
}

bool enQueue(Queue_t *queue, uint8_t data){
    if(queue == NULL){
        return false;
    }

    if(isQueueFull(queue)){
        uint8_t draft;
        printf("Queue: 0x%04X is Full!\n", queue);
        deQueue(queue, &draft);
    }

    queue->tail = (queue->tail + 1) % queue->capacity;
    memcpy(&queue->data[queue->tail], &data, sizeof(data));
    queue->size++;
    return true;
}

bool deQueue(Queue_t *queue, uint8_t *data){
    if(queue == NULL){
        return false;
    }

    if(isQueueEmpty(queue)){
        printf("Queue: 0x%04X is Empty!\n", queue);
        return false;
    }

    memcpy(data, &queue->data[queue->head], queue->dataSize);
    memset(&queue->data[queue->head], 0x00, queue->dataSize);

    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
    return true;
}

bool isQueueFull(Queue_t *queue){
    return (queue->size == queue->capacity);
}

bool isQueueEmpty(Queue_t *queue){
    return (queue->size == 0);
}

void main(void){
    Queue_t *brainstormer_queue = createQueue(10, sizeof(uint8_t));
    
    printf("is queue full?\r\n");
    printf("%02d\n", isQueueFull(brainstormer_queue));

    printf("is queue empty?\r\n");
    printf("%02d\n", isQueueEmpty(brainstormer_queue));

    // uint8_t draft = 0x55;
    // printf("Enqueue: %002d\r\n", enQueue(brainstormer_queue, draft));
    // draft = 0;

    printf("%02d %d\n", brainstormer_queue->size, brainstormer_queue->capacity);

    // printf("Dequeue: %02d\r\n", deQueue(brainstormer_queue, &draft));
    // printf("Item: %02x\r\n", draft);

    // Teste de enfileramento
    for(uint8_t i = 0; i < (brainstormer_queue->capacity + 10); i++) {
        printf("Enfiando %d ...\n", i);
        
        if(enQueue(brainstormer_queue, i) == false)
        {
            printf("Moio, ta cheio\n");
            break;
        }

        printf("Enfiado head: %02d - tail: %02d - data: %02d\n", 
        brainstormer_queue->head, 
        brainstormer_queue->tail, 
        brainstormer_queue->data[brainstormer_queue->tail]);
    }

    // Teste de desfileramento
    // for(uint8_t i = 0; i < brainstormer_queue->capacity + 1 ; i++) 
    // {
    //     uint8_t data = 0U;
        
    //     if(deQueue(brainstormer_queue, &data) == false)
    //         break;

    //     printf("Desenfiando %d\n", data);
    // }

    brainstormer_queue->ptr_hello();
}









