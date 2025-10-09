//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <chrono>
//using namespace std;
//
//class Solution {
//private:
//    mutex mtx;  // 互斥锁，保证输出不乱序
//
//public:
//    // 每个线程执行的任务函数
//    void work(const string& name) {
//        for (int progress = 100; progress >= 0; --progress) {
//            {
//                lock_guard<mutex> lock(mtx);
//                cout << name << "：当前装修进度为 " << progress << "%" << endl;
//            }
//            this_thread::sleep_for(chrono::milliseconds(50)); // 模拟耗时
//        }
//    }
//
//    // 启动三个线程
//    void run() {
//        thread t1(&Solution::work, this, "装修小组1");
//        thread t2(&Solution::work, this, "装修小组2");
//        thread t3(&Solution::work, this, "装修小组3");
//
//        t1.join();
//        t2.join();
//        t3.join();
//
//        cout << "装修完成！" << endl;
//    }
//};
//
//int main() {
//    Solution s;
//    s.run();
//    return 0;
//}
