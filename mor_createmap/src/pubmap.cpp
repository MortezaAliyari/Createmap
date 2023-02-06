#include "ros/ros.h"
#include "std_msgs/String.h"
#include <nav_msgs/OccupancyGrid.h>
#include <sstream>
#include <time.h>
#include <vector>
#include <thread>
#include <csignal>
using namespace std;

nav_msgs::OccupancyGrid map_;


void update_map(ros::Publisher map_pub){
  signal(SIGABRT, [](int signal_num){cout << "The interrupt signal is (" << signal_num
                                << "). \n";

                           // It terminates the  program
                           exit(signal_num);});
//  timespec start,end;
  map_.header.seq = 0;
  map_.header.frame_id = "map";

  map_.info.resolution = 0.5;
  map_.info.width = 20;
  map_.info.height = 20;
  ///
  map_.info.origin.position.x = 0;
  map_.info.origin.position.y =0;
  map_.info.origin.position.z = 0.0;
  map_.info.origin.orientation.x = 0.0;
  map_.info.origin.orientation.y = 0.0;
  map_.info.origin.orientation.z = 0.0;
  map_.info.origin.orientation.w = 1.0;
  while(1){
//    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
//    {
//      std::unique_lock<mutex> map_lock(lidar_mut);
//      map_cv.wait(map_lock,[this](){return this->map_ready;});
//      data=lid_data;
//      map_ready=false;
//    }
    cout<<"map data released"<<endl;
//    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
//    std::cout<<"timelapsed in map thread function is:"<<1.0/(this->time_elapsed(start,end))<<" Hz"<<std::endl;



  // this thread will wati for list of index from process_lidar thread to update map!

  ///
    map_.header.stamp = ros::Time::now();
    ///
    map_.info.map_load_time=ros::Time::now();
  map_.data.resize(map_.info.width * map_.info.height);
  std::vector<int8_t> a(map_.data.size(),-1);
//  std::vector<int> indexes=findmapindex(data);
//  int j=0;
//  for(auto& ind:indexes){
//    a[ind]=data.cellsvalue[j];
//    j++;
//  }
//  map_.data=std::move(a);
  vector<int8_t> dst(map_.data.size()/2,100);
  std::copy(dst.begin(), dst.end(), a.begin());

  map_.data=a;
  map_pub.publish(map_);

  this_thread::sleep_for(chrono::milliseconds(200));

 }
}
void signal_handler(int signal_num)
{
    cout << "The interrupt signal is (" << signal_num
         << "). \n";

    // It terminates the  program
    exit(signal_num);
}
int main(int argc, char **argv)
{

  ros::init(argc, argv, "pubmap");

  ros::NodeHandle n;

  ros::Publisher map_pub = n.advertise<nav_msgs::OccupancyGrid>("map", 1);

  ros::Rate loop_rate(1);
  signal(SIGABRT, signal_handler);

//  map_.header.seq = 0;
//  map_.header.stamp = ros::Time::now();
//  map_.header.frame_id = "map";
//  ///
//  map_.info.map_load_time=ros::Time::now();
//  map_.info.resolution = 0.5;
//  map_.info.width = 20;
//  map_.info.height = 20;
//  ///
//  map_.info.origin.position.x = -5;
//  map_.info.origin.position.y =-5;
//  map_.info.origin.position.z = 0.0;
//  map_.info.origin.orientation.x = 0.0;
//  map_.info.origin.orientation.y = 0.0;
//  map_.info.origin.orientation.z = 0.0;
//  map_.info.origin.orientation.w = 1.0;
//  ///

//  map_.data.resize(map_.info.width * map_.info.height);
//  vector<int8_t> a(map_.data.size(),-1);
//  vector<int8_t> dst(map_.data.size()/2,100);
//  std::copy(dst.begin(), dst.end(), a.begin());

//  map_.data=a;
      /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  ROS_INFO("==========Target is creating a map of unknown environment==========");

    /**
     * This is a message object. You stuff it with data, and then publish it.
     */



    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
//    map_pub.publish(map_);
thread t(update_map,map_pub);
    ros::spinOnce();
t.join();
//    loop_rate.sleep();



  return 0;
}
