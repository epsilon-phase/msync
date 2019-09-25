#ifndef _QUEUES_HPP_
#define _QUEUES_HPP_

#include <string>
#include <vector>

#include "queue_list.hpp"

enum class queues
{
    fav,
    boost,
    post
};

void enqueue(queues toenqueue, const std::string& account, const std::vector<std::string>& add);

// dequeue mutates and moves from the vector for efficiency
void dequeue(queues todequeue, const std::string& account, std::vector<std::string>&& remove);
void clear(queues toclear, const std::string& account);

queue_list get(queues toget, const std::string& account);

std::vector<std::string> print(queues toprint, const std::string& account);

#endif