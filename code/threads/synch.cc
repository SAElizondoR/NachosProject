// synch.cc
//      Routines for synchronizing threads.  Three kinds of
//      synchronization routines are defined here: semaphores, locks
//      and condition variables (the implementation of the last two
//      are left to the reader).
//
// Any implementation of a synchronization routine needs some
// primitive atomic operation.  We assume Nachos is running on
// a uniprocessor, and thus atomicity can be provided by
// turning off interrupts.  While interrupts are disabled, no
// context switch can occur, and thus the current thread is guaranteed
// to hold the CPU throughout, until interrupts are reenabled.
//
// Because some of these routines might be called with interrupts
// already disabled (Semaphore::V for one), instead of turning
// on interrupts at the end of the atomic operation, we always simply
// re-set the interrupt state back to its original value (whether
// that be disabled or enabled).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synch.h"
#include "system.h"

NodeThread::NodeThread() {
    data = 0;
    next = NULL;
}

NodeThread::~NodeThread() {
    delete next;
}

NodeThread::NodeThread(Thread* t) {
    data = t;
    next = NULL;
}

LinkedListThreads::LinkedListThreads() {
    head = end = NULL;
}

void LinkedListThreads::append(Thread* data) {
    NodeThread* newNode = new NodeThread(data);
    if (head == NULL) {
    head = end = newNode;
    return;
    }
    end->next = newNode;
    end = newNode;
}

bool LinkedListThreads::isEmpty() {
    return head == NULL;
}

Thread* LinkedListThreads::remove() {
    if (head == NULL)
        return NULL;
    
    NodeThread *tmp = head;
    head = head->next;
    return tmp->data;
    }

//----------------------------------------------------------------------
// Semaphore::Semaphore
//      Initialize a semaphore, so that it can be used for synchronization.
//
//      "debugName" is an arbitrary name, useful for debugging.
//      "initialValue" is the initial value of the semaphore.
//----------------------------------------------------------------------

Semaphore::Semaphore (const char *debugName, int initialValue)
{
    name = debugName;
    value = initialValue;
    queue = new List;
}

//----------------------------------------------------------------------
// Semaphore::Semaphore
//      De-allocate semaphore, when no longer needed.  Assume no one
//      is still waiting on the semaphore!
//----------------------------------------------------------------------

Semaphore::~Semaphore ()
{
    delete queue;
    queue = NULL;
    value = -1;
}

//----------------------------------------------------------------------
// Semaphore::P
//      Wait until semaphore value > 0, then decrement.  Checking the
//      value and decrementing must be done atomically, so we
//      need to disable interrupts before checking the value.
//
//      Note that Thread::Sleep assumes that interrupts are disabled
//      when it is called.
//----------------------------------------------------------------------

void
Semaphore::P ()
{
    IntStatus oldLevel = interrupt->SetLevel (IntOff);	// disable interrupts

    ASSERT_MSG(value >= 0, "Semaphore became negative!?\n");

    while (value == 0)
      {				// semaphore not available
          queue->Append ((void *) currentThread);        // so go to sleep
          currentThread->Sleep ();
      }
    value--;			// semaphore available,
    // consume its value

    (void) interrupt->SetLevel (oldLevel);	// re-enable interrupts
}

//----------------------------------------------------------------------
// Semaphore::V
//      Increment semaphore value, waking up a waiter if necessary.
//      As with P(), this operation must be atomic, so we need to disable
//      interrupts.  Scheduler::ReadyToRun() assumes that threads
//      are disabled when it is called.
//----------------------------------------------------------------------

void
Semaphore::V ()
{
    Thread *thread;
    IntStatus oldLevel = interrupt->SetLevel (IntOff);

    ASSERT_MSG(value >= 0, "Semaphore became negative!?\n");

    thread = (Thread *) queue->Remove ();
    if (thread != NULL)		// make thread ready, consuming the V immediately
        scheduler->ReadyToRun (thread);
    value++;
    (void) interrupt->SetLevel (oldLevel);
}

#ifdef CHANGED

//----------------------------------------------------------------------
// Lock::Lock
//      Initialize a lock, so that it can be used for syhchronization.
//
//      "debugName" is an arbitrary name, useful for debugging.
//----------------------------------------------------------------------

Lock::Lock (const char *debugName)
{
    name = debugName;
    // ASSERT_MSG(FALSE, "TODO\n");
    owner = NULL;
}

//----------------------------------------------------------------------
// Lock::~Lock
//      Deallocate lock, when no longer needed.
//----------------------------------------------------------------------

Lock::~Lock ()
{
}

//----------------------------------------------------------------------
// Lock::Acquire
//      Wait until the lock is free atomically.
//----------------------------------------------------------------------
void
Lock::Acquire ()
{
    while (owner != NULL);

    // disable interrupts
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    owner = currentThread;
    interrupt->SetLevel(oldLevel);  // enable interrupts
}

//----------------------------------------------------------------------
// Lock::Release
//      Set the lock free atomically
//----------------------------------------------------------------------

void
Lock::Release ()
{
    while (!isHeldByCurrentThread());
    // ASSERT_MSG(isHeldByCurrentThread(), "Il n'est pas possible de 
    //     libérer un verrou d'un autre thread\n");
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    owner = NULL;
    interrupt->SetLevel(oldLevel);
}

bool
Lock::isHeldByCurrentThread ()
{
    return owner == currentThread;
}

//----------------------------------------------------------------------
// Condition::Condition
//      Initialize a condition variable, so that it can be used for
//      syhchronization.
//
//      "debugName" is an arbitrary name, useful for debugging.
//----------------------------------------------------------------------

Condition::Condition (const char *debugName)
{
    name = debugName;
    // ASSERT_MSG(FALSE, "TODO\n");
}

//----------------------------------------------------------------------
// Condition::~Condition
//      Deallocate condition variable, when no longer needed.
//----------------------------------------------------------------------

Condition::~Condition ()
{
}

//----------------------------------------------------------------------
// Condition::Wait
//      Wait until the lock is free atomically.
//----------------------------------------------------------------------

void
Condition::Wait (Lock * conditionLock)
{
    ASSERT_MSG(conditionLock->isHeldByCurrentThread(), "Wrong thread\n");

    conditionLock->Release();
    wait->append(currentThread);
    // currenThread->Sleep();
    conditionLock->Acquire();
}

//----------------------------------------------------------------------
// Condition::Signal
//      Wake one process.
//----------------------------------------------------------------------

void
Condition::Signal (Lock * conditionLock)
{
    ASSERT_MSG(conditionLock->isHeldByCurrentThread(), "Wrong thread\n");

    if (!wait->isEmpty()) {
        Thread* t = wait->remove();
        // t->Start();
    }
}
void
Condition::Broadcast (Lock * conditionLock)
{
    ASSERT_MSG(conditionLock->isHeldByCurrentThread(), "Wrong thread\n");

    while (!wait->isEmpty()) {
        Signal(conditionLock);
    }
}

#endif // CHANGED
