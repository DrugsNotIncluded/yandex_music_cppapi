#include <stdlib.h>
#include <iostream>
#include <future>
#include "types.hpp"
#include "client.hpp"
#include "config.hpp"

int
main(int argc, char *argv[]) {
	const std::string token = load_token_from_file("token_file");
	Client client = Client(token);
	json tracks = client.async_user_likes_tracks().get()["result"]["library"]["tracks"];
	auto tracks_info = client.async_tracks_download_info(tracks);
	std::cout << tracks_info[3].get() << std::endl;

	return 0;
}
