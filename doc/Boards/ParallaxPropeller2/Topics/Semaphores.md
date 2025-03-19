[Parallax Propeller 2](../ParallaxPropeller2.md)
# Semaphores
In computer science, a semaphore is a variable or abstract data type used to control access to a common resource by multiple threads and avoid critical section problems in a concurrent system such as a multitasking operating system.

# Propeller Programming Idioms
| Method | Description |
| --- | --- |
| LOCKNEW() : LockNum | Check out a new LOCK from inventory, LockNum = 0..15 if successful or < 0 if no LOCK available. |
| LOCKRET(LockNum) | Return a certain LOCK to inventory. |
| LOCKTRY(LockNum) : LockState | Try to capture a certain LOCK, LockState = -1 if successful or 0 if another cog has captured the LOCK. |
| LOCKREL(LockNum) | Release a certain LOCK. |
| LOCKCHK(LockNum) : LockState | Check a certain LOCK's state, LockState[31] = captured, LockState[3:0] = current or last owner cog. |

# References
- [Wikipedia](https://en.wikipedia.org/wiki/Semaphore_(programming))


