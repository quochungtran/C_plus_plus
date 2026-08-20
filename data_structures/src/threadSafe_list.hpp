#pragma once

#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <utility>
#include <vector>


/**
 * Instead of one mutex protecting the whole list, every node has its own mutex
 * A thread walks the list by locking node N, then locking node N+1 before releasing N's lock
 * then releasing N 's lock.
 * 
 * It prevents another thread from slicing in or deleting a node in the gap between your locks.
 * 
 * 
 * Concurrency:
 * Different threads can be working on different nodes in the list at the same time, wherether they are 
 * processing each item with for_each(), find_first_if() or removing item remove_if()
 * 
 * But because the mutex for each node must be locked in turn, the thread cant pass each other.
 * If one thread is spending a long time processing a paricular node, other threads will
 * have to wait when they reach that particular node
 */

namespace data_structure {

template <typename T>
class ThreadSafeList{
private:
    struct Node {
        std::mutex m;
        std::shared_ptr<T> data;
        std::unique_ptr<Node> next;
        
        Node(): next() 
        {}
        
        Node(const T& value):
            data(std::make_shared<T>(value))
        {}
    };

    Node head;
public:

    // rule of 5
    ThreadSafeList(){}
    ~ThreadSafeList(){
        remove_if([](const T&){return true;});
    }
    ThreadSafeList& operator=(const ThreadSafeList& other) = delete;
    ThreadSafeList (const ThreadSafeList& other) = delete;

    
    void push_front(const T& value){
        std::unique_ptr<Node> newNode (new Node(value));
        std::lock_guard<std::mutex> lk(head.m);
        newNode->next = std::move(head.next);
        head.next = std::move(newNode);
    }
    
    template <typename Function>
    void for_each(Function f){
        Node* curr = &head;
        std::unique_lock<std::mutex> lk(head.m);
        while (Node* const next_curr = curr->next.get()){
            std::unique_lock<std::mutex> next_lk(next_curr->m);
            lk.unlock();
            f(*next_curr->data);
            curr = next_curr;
            lk = std::move(next_lk);
        }

    }

    template <typename Predicate>
    std::shared_ptr<T> find_first_if(Predicate p){
        Node* curr = &head;
        std::unique_lock<std::mutex> lk(head.m);
        while (Node* const next_curr = curr->next.get()){
            std::unique_lock<std::mutex> next_lk(next_curr->m);
            lk.unlock();
            if (p(*next_curr->data)){
                return next_curr->data;
            }
            curr = next_curr;
            lk= std::move(next_lk);
        }
        return std::shared_ptr<T>();
    }

    template <typename Predicate>
    void remove_if(Predicate p){
        Node* curr = &head;
        std::unique_lock<std::mutex> lk(head.m);

        while (Node* const next_curr = curr->next.get()){
            std::unique_lock<std::mutex> next_lk(next_curr->m);
            if (p(*next_curr->data)){
                std::unique_ptr<Node> old_next = std::move(curr->next);
                curr->next = std::move(next_curr->next);
                next_lk.unlock();
            }
            else {
                lk.unlock();
                curr = next_curr;
                lk = std::move(next_lk);
            }
        }
    }
};

}