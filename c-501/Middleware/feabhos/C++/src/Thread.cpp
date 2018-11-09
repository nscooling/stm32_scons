/*
DISCLAIMER:
Feabhas is furnishing this item "as is". Feabhas does not provide any warranty
of the item whatsoever, whether express, implied, or statutory, including, but
not limited to, any warranty of merchantability or fitness for a particular
purpose or any warranty that the contents of the item will be error-free.
In no respect shall Feabhas incur any liability for any damages, including, but
limited to, direct, indirect, special, or consequential damages arising out of,
resulting from, or any way connected to the use of the item, whether or not
based upon warranty, contract, tort, or otherwise; whether or not injury was
sustained by persons or property or otherwise; and whether or not loss was
sustained from, or arose out of, the results of, the item, or any services that
may be provided by Feabhas.
*/
#include "Thread.h"
#include "Scheduler.h"

namespace feabhOS
{
  Thread::Thread() :
    pRunObject(NULL),
    handle(0),
    priority(DefaultPriority),
    stack(DefaultStack),
    done(true),
    created(false)
  {
  }


  Thread::Thread(Thread::Priority prio) :
    pRunObject(NULL),
    handle(0),
    priority(prio),
    stack(DefaultStack),
    done(true),
    created(false)
  {
  }


  Thread::Thread(Thread::Stack stacksize) :
    pRunObject(NULL),
    handle(0),
    priority(DefaultPriority),
    stack(stacksize),
    done(true),
    created(false)
  {
  }


  Thread::Thread(Thread::Priority prio, Thread::Stack stacksize) :
    pRunObject(NULL),
    handle(0),
    priority(prio),
    stack(stacksize),
    done(true),
    created(false)
  {
  }


  Thread::~Thread()
  {
    if(created)
    {
      if(!done)
      {
        // TO DO:
        // There should be some error recorded here
        // as we've terminated the thread prematurely - 
        // it's going out of scope, but still running!
      }
      feabhOS_task_destroy(&handle);
    }
  }


  feabhOS_error Thread::start(IRunnable& obj)
  {
    feabhOS_error error;

    // Check to see if start has already been called on this thread
    // object.  Return an error if this is the case - 
    // otherwise, the original OS thread would be leaked!
    //
    if(created) return ERROR_STUPID;

    pRunObject = &obj;

    error = feabhOS_task_create(&handle,
                                &Thread::scheduledFunction,
                                reinterpret_cast<Thread*>(this),
                                static_cast<feabhOS_stack_size_t>(stack),
                                static_cast<feabhOS_priority_t>(priority));

    created = (error == ERROR_OK);
    return error;
  }
 

  int Thread::scheduledFunction(void* arg)
  {
    Thread* thisThread = (reinterpret_cast<Thread*>(arg));
    thisThread->schedulePolicy();
    return 1;
  }


  void Thread::schedulePolicy()
  {
    do
    {
      done = pRunObject->run();
    } while(!done);
  }


  void Thread::join()
  {
    if(!created)
    {
      return;
    }
    else
    {
      feabhOS_task_join(&handle);
    } 
  }


  void Thread::sleep(duration_mSec_t period)
  {
    feabhOS_task_sleep(period);
  }


  void Thread::yield()
  {
    feabhOS_task_yield();
  }
}
