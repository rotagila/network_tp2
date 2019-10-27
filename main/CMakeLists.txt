cmake_minimum_required(VERSION 3.10)

set(replication_sources src/main.cpp
                        src/game_object.cpp
                        src/streams.cpp
						src/Enemy.cpp
						src/Player.cpp
						src/ClassRegistry.cpp
						src/Server.cpp
						src/Client.cpp
						src/LinkingContext.cpp
						)

include_directories(include)
set(replication_headers include/game_object.hpp
                        include/utils.hpp
                        include/streams.hpp
						include/Enemy.hpp
						include/LinkingContext.hpp
						include/Player.hpp
						include/ClassRegistry.hpp
						include/ReplicationManager.hpp
						include/Server.hpp
						include/Client.hpp
						)

add_executable(tp2 ${replication_sources} ${replication_headers})
target_link_libraries(tp2 PUBLIC uvw_interface GSL)