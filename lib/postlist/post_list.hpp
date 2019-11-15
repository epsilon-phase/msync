#ifndef _POST_LIST_HPP_
#define _POST_LIST_HPP_

#include <filesystem.hpp>

#include <fstream>

#include "../entities/entities.hpp"

// these should be ostreams, but I didn't want to pull in the whole iostream library just for this
std::ofstream& operator<<(std::ofstream& out, const mastodon_status& status);
std::ofstream& operator<<(std::ofstream& out, const mastodon_notification& notification);

// currently supposed to work with statuses and notifications
template <typename post_type>
class post_list
{
public:
	post_list(const fs::path& filename) : outfile(filename, std::ios::app | std::ios::ate | std::ios::out)
	{
	}

	void write(const post_type& post)
	{
		// this assumes that the operator<< for post adds a newline at the end
		outfile << post;
		outfile << "--------------\n";
	}

private:
	std::ofstream outfile;
};
#endif