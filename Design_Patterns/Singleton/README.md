# Singleton Design Pattern Implementations in Java

The Singleton design pattern ensures that a class has only one instance and provides a global point of access to it. Below, we explore three implementations of the Singleton pattern, each addressing different requirements such as lazy loading, thread safety, and performance optimization.

## 1. Lazy Initialization Singleton

The `LazyDBConnection` class creates a singleton instance only when it is first requested. This implementation avoids resource wastage by not initializing the instance at class loading time.

### Code
```java
public class LazyDBConnection {
    private static LazyDBConnection connection;

    private LazyDBConnection() {}

    // Singleton instance is created only when it's first requested.
    // Not thread-safe, as multiple threads accessing this method can lead to multiple instances.
    public static LazyDBConnection getInstance() {
        if (connection == null) {
            connection = new LazyDBConnection();
        }
        return connection;
    }
}
```
### Explanation
1. **Lazy Loading :** The instance is created only on the first call to getInstance().
2. **Thread Safety Issue:** Not thread-safe, as two threads accessing getInstance() simultaneously could create multiple instances.
**Use Case:** Suitable for single-threaded environments.


## 2. Synchronized Singleton
The `SyncDBConnection` class improves upon the lazy initialization approach by adding thread-safety through the `synchronized` keyword. However, this incurs a performance overhead due to synchronization.



### Code
```java
public class SyncDBConnection {
    private static SyncDBConnection connection;

    private SyncDBConnection() {}

    // Below code is thread-safe.
    //But every time getInstance is called there is performance overhead
    // Lock is created every time function is called either conn == null or not 
    // Locks created = No of Threads
    synchronized public static SyncDBConnection getInstance() {
        if (connection == null) {
            connection = new SyncDBConnection();
        }
        return connection;
    }
}

``` 
### Explanation
1. **Thread Safety:** The synchronized method ensures that only one thread can create the instance, preventing multiple instances in multi-threaded scenarios.
2. **Performance Overhead:** Synchronization incurs a performance penalty as it locks the method for every call, even if the instance is already created.

**Use Case:** Suitable for applications where thread-safety is critical but performance is less of a concern.

## 3. Double-Checked Locking Singleton

The `DoubleLockDBConnection` class uses double-checked locking to minimize synchronization overhead while maintaining thread safety. This implementation reduces unnecessary locking once the instance is initialized.

### Code 
```java
public class DoubleLockDBConnection {
    private static DoubleLockDBConnection connection;

    private DoubleLockDBConnection() {}

    // This involves checking if the singleton instance is null before acquiring a lock.
    // If the instance is null, only then is the lock acquired to create the instance.
    public static DoubleLockDBConnection getInstance() {
        if (connection == null) {
            // Maximum Lock == 2 , when 2 thread tries to compete here
            synchronized (DoubleLockDBConnection.class) {
                if (connection == null) {
                    // Due to synchronized only 1 thread reaches here and initialize
                    connection = new DoubleLockDBConnection();
                }
            }
        }
        return connection;
    }
}
```

### Explanation
1. **Double-Checked Locking:** The instance is checked twice to avoid unnecessary synchronization once the instance is initialized.
2. **Thread Safety:** Ensures that only one instance is created in multi-threaded environments.
3. **Performance:** Reduces synchronization overhead compared to the SyncDBConnection by limiting it to the initial creation phase only.
**Use Case:** Ideal for high-performance, multi-threaded applications where thread safety and resource efficiency are essential.



### Summary Table

| Implementation	    | Thread Safety | Performance Overhead | Best Use Case |
| --------              | -------       | -------              | -------       |
| Lazy Initialization	| No            | Low                  | Single-threaded environments |
| Synchronized Singleton | Yes          | High                 | Multi-threaded applications, low traffic |
| Double-Checked Locking | Yes          | Low                   | High-performance, multi-threaded systems |


## Fixing Double-Checked Locking in Singleton Pattern

The two critical memory issues with the double-checked locking solution of the Singleton pattern and provides a fix using the `volatile` keyword.

### Overview
The double-checked locking Singleton pattern is widely used to ensure a class has only one instance while optimizing for multi-threaded environments. However, it has inherent memory issues in Java due to:
1. **Instruction Reordering** – Causing uninitialized fields to be accessed by threads.
2. **Caching (L1 Cache Issue)** – Where threads in different CPU cores may not see the latest instance due to cache synchronization delays.

### Issue 1: Instruction Reordering
In multi-threaded scenarios, the CPU may reorder instructions to optimize performance. When initializing the Singleton instance, instruction reordering could lead to a scenario where the instance reference is assigned before all its fields are initialized. This causes other threads to see a partially initialized instance, leading to incorrect behavior.

#### Code example 
```java 
public static DBConnection getInstance() {
    if (conObject == null) {
        synchronized (DBConnection.class) {
            if (conObject == null) {
                memoryPointer = allocateMemory();
                conObject = memoryPointer;
                memoryPointer.memberVariable = initializeVariable();
            }
        }
    }
    return conObject;
}

```

#### Example of Reordering Steps:
1. Allocate memory for the instance.
2. Assign reference to the instance.
3. Initialize instance fields.

If Step 2 is reordered to happen before Step 3, other threads may access the instance with uninitialized fields.

### Issue 2: L1 Caching Issue
Each CPU core has its cache, where variables are stored temporarily. When an instance is created in one core, it might not immediately update in the main memory. Consequently, another thread accessing the Singleton instance from a different core may not see the latest reference, leading to multiple instance creations and breaking the Singleton constraint.

### Solution: Using the `volatile` Keyword
To solve both issues, the Singleton instance variable is declared as `volatile`. The `volatile` keyword has two key properties:
1. **Memory Synchronization**: It ensures all threads see the latest value directly from memory, bypassing cache.
2. **Order of Operations**: It prevents reordering of instructions around the volatile variable, ensuring correct initialization order.

#### Updated Java Code

```java
public class DoubleLockDBConnection {
    // Declaring the instance as volatile to prevent memory consistency issues.
    private static volatile DoubleLockDBConnection connection;
    
    private DoubleLockDBConnection() {} // Private constructor to prevent instantiation.

    // Double-checked locking with synchronized block to ensure single instance creation.
    public static DoubleLockDBConnection getInstance() {
        if (connection == null) { // First check without locking.
            synchronized (DoubleLockDBConnection.class) {
                if (connection == null) { // Second check with locking.
                    connection = new DoubleLockDBConnection();
                }
            }
        }
        return connection;
    }
}
```