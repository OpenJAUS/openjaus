#include "LocalComponent.h"
#include "timeval.h"

void LocalComponent::run()
{
	struct timespec timeout;
	struct timeval now;
		
	if(!this->cmpt)
	{
		// ERROR: This cannot be called if we haven't yet constructed our component
		// TODO: Throw an exception? Log an error.
		return;
	}

	// Lock our mutex
	pthread_mutex_lock(&this->threadMutex);
	
	// prepare new timeout value.
	// Note that we need an absolute time.
	gettimeofday(&now, NULL);
	timeout.tv_sec = now.tv_sec;

	// timeval uses micro-seconds.
	// timespec uses nano-seconds.
	// 1 micro-second = 1000 nano-seconds.
	timeout.tv_nsec = (now.tv_usec * 1000) + (long)(1e9 / this->cmptRateHz);

	while(this->running)
	{
		if(timeout.tv_nsec > 1e9)
		{
			timeout.tv_nsec = timeout.tv_nsec % (long)1e9;
			timeout.tv_sec++;
		}
		
		int rc = pthread_cond_timedwait(&this->threadConditional, &this->threadMutex, &timeout);
		switch(rc)
		{
			case 0: // Conditional Signal
				// Check the send queue
				while(!this->queue.isEmpty())
				{
					// Pop a packet off the queue and send it off
					processMessage(queue.pop());

					// Check if we need to run our state thread!
					gettimeofday(&now, NULL);
					if( now.tv_sec > timeout.tv_sec || (now.tv_usec*1000) > timeout.tv_nsec)
					{
						break;
					}
				}
				break;
			
			case ETIMEDOUT: // our time is up
				// Capture time now, that way we get a constant deltaTime from beginning to beginning
				gettimeofday(&now, NULL);
				switch(cmpt->state)
				{
					case JAUS_INITIALIZE_STATE:
						intializeState();
						break;

					case JAUS_STANDBY_STATE:
						standbyState();
						break;

					case JAUS_READY_STATE:
						readyState();
						break;

					case JAUS_EMERGENCY_STATE:
						emergencyState();
						break;

					case JAUS_FAILURE_STATE:
						failureState();
						break;
					
					default:
						//do nothing
						break;
				}
				allState();

				// prepare new timeout value.
				// Note that we need an absolute time.
				timeout.tv_sec = now.tv_sec;

				// timeval uses micro-seconds.
				// timespec uses nano-seconds.
				// 1 micro-second = 1000 nano-seconds.
				timeout.tv_nsec = (now.tv_usec * 1000) + (long)(1e9 / this->cmptRateHz);

				while(!this->queue.isEmpty())
				{
					// Pop a packet off the queue and send it off
					processMessage(queue.pop());
					
					// Check if we need to run our state thread!
					gettimeofday(&now, NULL);
					if( now.tv_sec > timeout.tv_sec || (now.tv_usec*1000) > timeout.tv_nsec)
					{
						break;
					}
				}
				break;

			default:
				// Some other error occured
				// TODO: Log error.
				usleep(100);				
				gettimeofday(&now, NULL);

				// prepare new timeout value.
				// Note that we need an absolute time.
				timeout.tv_sec = now.tv_sec;

				// timeval uses micro-seconds.
				// timespec uses nano-seconds.
				// 1 micro-second = 1000 nano-seconds.
				timeout.tv_nsec = (now.tv_usec * 1000) + (long)(1e9 / this->cmptRateHz);
				break;
		}
	}
	
	pthread_mutex_unlock(&this->threadMutex);
	shutdownState();
}

