#include <stdio.h>
#include <thread>
#include <cstdlib>
#include "CycleTimer.h"

typedef struct {
    float x0, x1;
    float y0, y1;
    unsigned int width;
    unsigned int height;
    int maxIterations;
    int* output;
    int threadId;
    int numThreads;
} WorkerArgs;


extern void mandelbrotSerial(
    float x0, float y0, float x1, float y1,
    int width, int height,
    int startRow, int numRows,
    int maxIterations,
    int output[]);


//
// workerThreadStartStatic --
//
// Static allocation version
void workerThreadStartStatic(WorkerArgs * const args) {
    double startTime = CycleTimer::currentSeconds();
    int perThreadRows = args->height / args->numThreads;
    int paddingRows = args->height % args->numThreads;
    int startRow = args->threadId * perThreadRows;
    int totalRows;
    if (args->threadId == args->numThreads - 1)
        totalRows = perThreadRows + paddingRows;
    else
        totalRows = perThreadRows;
    
    mandelbrotSerial(args->x0, args->y0, args->x1, args->y1, args->width, args->height,
                     startRow, totalRows, args->maxIterations, args->output);

    double endTime = CycleTimer::currentSeconds();
    double costTime = (endTime - startTime) * 1000;
    printf("Thread %d (static): total time=%f ms, startRow=%d, totalRows=%d, perThreadRows=%d, paddingRows=%d\n", 
           args->threadId, costTime, startRow, totalRows, perThreadRows, paddingRows);
}

//
// workerThreadStartChunk --
//
// Chunk-based allocation version
void workerThreadStartChunk(WorkerArgs * const args) {
    double startTime = CycleTimer::currentSeconds();
    unsigned int chunkRows = 40;
    unsigned int startRow = args->threadId * chunkRows;
    while (true) {
        if ((startRow + chunkRows) < args->height) {
            mandelbrotSerial(args->x0, args->y0, args->x1, args->y1, args->width, args->height,
                             startRow, chunkRows, args->maxIterations, args->output);
            startRow = startRow + args->numThreads * chunkRows;
        } else {
            if (startRow < args->height) {
                mandelbrotSerial(args->x0, args->y0, args->x1, args->y1, args->width, args->height,
                                 startRow, args->height - startRow, args->maxIterations, args->output);
                break;
            } else if (startRow >= args->height) {
                break;
            }
        }
    }
    double endTime = CycleTimer::currentSeconds();
    double costTime = (endTime - startTime) * 1000;
    printf("Thread %d (chunk): total time=%f ms, chunkRows=%d, final startRow=%d\n", 
           args->threadId, costTime, chunkRows, startRow);
}

//
// MandelbrotThreadStatic --
//
// Multi-threaded implementation using static allocation.
void mandelbrotThreadStatic(
    int numThreads,
    float x0, float y0, float x1, float y1,
    int width, int height,
    int maxIterations, int output[])
{
    static constexpr int MAX_THREADS = 40;

    if (numThreads > MAX_THREADS)
    {
        fprintf(stderr, "Error: Max allowed threads is %d\n", MAX_THREADS);
        exit(1);
    }

    // Creates thread objects that do not yet represent a thread.
    std::thread workers[MAX_THREADS];
    WorkerArgs args[MAX_THREADS];

    for (int i=0; i<numThreads; i++) {
        args[i].x0 = x0;
        args[i].y0 = y0;
        args[i].x1 = x1;
        args[i].y1 = y1;
        args[i].width = width;
        args[i].height = height;
        args[i].maxIterations = maxIterations;
        args[i].numThreads = numThreads;
        args[i].output = output;
        args[i].threadId = i;
    }

    // Spawn the worker threads.
    for (int i=1; i<numThreads; i++) {
        workers[i] = std::thread(workerThreadStartStatic, &args[i]);
    }
    
    workerThreadStartStatic(&args[0]);

    // join worker threads
    for (int i=1; i<numThreads; i++) {
        workers[i].join();
    }
}

//
// MandelbrotThreadChunk --
//
// Multi-threaded implementation using chunk-based allocation.
void mandelbrotThreadChunk(
    int numThreads,
    float x0, float y0, float x1, float y1,
    int width, int height,
    int maxIterations, int output[])
{
    static constexpr int MAX_THREADS = 40;

    if (numThreads > MAX_THREADS)
    {
        fprintf(stderr, "Error: Max allowed threads is %d\n", MAX_THREADS);
        exit(1);
    }

    // Creates thread objects that do not yet represent a thread.
    std::thread workers[MAX_THREADS];
    WorkerArgs args[MAX_THREADS];

    for (int i=0; i<numThreads; i++) {
        args[i].x0 = x0;
        args[i].y0 = y0;
        args[i].x1 = x1;
        args[i].y1 = y1;
        args[i].width = width;
        args[i].height = height;
        args[i].maxIterations = maxIterations;
        args[i].numThreads = numThreads;
        args[i].output = output;
        args[i].threadId = i;
    }

    // Spawn the worker threads.
    for (int i=1; i<numThreads; i++) {
        workers[i] = std::thread(workerThreadStartChunk, &args[i]);
    }
    
    workerThreadStartChunk(&args[0]);

    // join worker threads
    for (int i=1; i<numThreads; i++) {
        workers[i].join();
    }
}

