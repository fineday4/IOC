#include "IocContainer.h"
#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <iostream>

using namespace std;

struct ICar {
    virtual ~ICar() {}
    virtual void run() = 0;
};

struct Car: public ICar {
    void run() {
        cout << "Car::run()" << endl;
    }
};

struct Bus: public ICar {
    void run() {
        cout << "Bus::run()" << endl;
    }
};

struct BYDCar: public ICar {
public:
    BYDCar(const string &ower, const string &id, const int& money): _owner(ower), _id(id), _money(money) {}

    void run() {
        cout << "money: " << _money << " ower: " << _owner << " _id: " << _id << endl;
    }

private:
    string _owner;
    string _id;
    int _money;
};

struct Driver {
public:
    Driver(ICar* ptr): m_car(ptr) {
        cout << "Driver constructor" << endl;
    }

    void test() {
        if(m_car) {
            m_car->run();
        }
    }

private:
    ICar* m_car;
};

struct DZCar: ICar {};

#if 0
Driver* getADriver(const string condition)
{
    Driver* man = nullptr;
    if(conditionCar) {
        man = new Driver(new Car);
    } else if(conditionBus) {
        man = new Driver(new Bus);
    } else if(conditionBYD) {
        man = new Driver(new BYDCar("tester", "13214", 34));
    } else if(conditionDZ) {
        man = new Driver(new DZCar("tester", "13214", 34));

    }
    ...
    return man;
}
#endif
/**
 * @brief RegisterDepend无参测试1
 * 正常获取对象
 * 
 */
TEST(IocContainerTest, case1) {
    IocContainer ioc;
    ioc.Register<Driver, Car>("CarDriver");
    ioc.Register<Driver, Bus>("BusDriver");
    
    shared_ptr<Driver> CarDriver = ioc.ResolveShared<Driver>("CarDriver");
    CarDriver->test();

    shared_ptr<Driver> BusDriver = ioc.ResolveShared<Driver>("BusDriver");
    BusDriver->test();
}

/**
 * @brief RegisterDepend无参测试2
 * 异常获取对象
 */
TEST(IocContainerTest, case2) {
    IocContainer ioc;
    ioc.Register<Driver, Car>("CarDriver");
    ioc.Register<Driver, Bus>("BusDriver");
    
    shared_ptr<Driver> CarDriver = ioc.ResolveShared<Driver>("CarDriverNone");
    CarDriver->test();

    shared_ptr<Driver> BusDriver = ioc.ResolveShared<Driver>("BusDriverNone");
    BusDriver->test();
}
/**
 * @brief RegisterDepend有参测试1
 * 正常获取对象
 * 
 */
TEST(IocContainerTest, case3) {
    IocContainer ioc;
    ioc.Register<Driver, BYDCar, const string&, const string&, const int&>("CarDriver");
    
    shared_ptr<Driver> CarDriver = ioc.ResolveShared<Driver, const string&, const string&, const int&>("CarDriver", "myCar", "123412344", 26);
    CarDriver->test();
}

/**
 * @brief RegisterDepend有参测试2
 * 异常获取对象
 */
TEST(IocContainerTest, case4) {
    IocContainer ioc;
    ioc.Register<Driver, BYDCar, const string&, const string&, const int&>("CarDriver");
    
    shared_ptr<Driver> CarDriver = ioc.ResolveShared<Driver, const string&, const string&, const int&>("CarDriverNone", "myCar", "123412344", 26);
    CarDriver->test();
}

/**
 * @brief Register无参测试1
 * 正常获取对象
 * 
 */
TEST(IocContainerTest, case5) {
    IocContainer ioc;
    ioc.RegisterNormal<Car>("CarDriverRegisterTest");
    ioc.RegisterNormal<Bus>("BusDriverRegisterTest");
    
    shared_ptr<Car> CarDriver = ioc.ResolveShared<Car>("CarDriverRegisterTest");
    CarDriver->run();

    shared_ptr<Bus> BusDriver = ioc.ResolveShared<Bus>("BusDriverRegisterTest");
    BusDriver->run();
}

/**
 * @brief Register无参测试2
 * 异常获取对象
 * 
 */
TEST(IocContainerTest, case6) {
    IocContainer ioc;
    ioc.RegisterNormal<Car>("CarDriverRegisterTest");
    ioc.RegisterNormal<Bus>("BusDriverRegisterTest");
    
    shared_ptr<Car> CarDriver = ioc.ResolveShared<Car>("CarDriverNone");
    CarDriver->run();

    shared_ptr<Bus> BusDriver = ioc.ResolveShared<Bus>("BusDriverNone");
    BusDriver->run();
}

/**
 * @brief Register有参测试1
 * 正常获取对象
 * 
 */
TEST(IocContainerTest, case7) {
    IocContainer ioc;
    ioc.RegisterNormal<BYDCar, const string&, const string&, const int&>("BYDCarDriver");
    
    shared_ptr<BYDCar> CarDriver = ioc.ResolveShared<BYDCar, const string&, const string&, const int&>("BYDCarDriver", "myCar", "123412344", 26);
    CarDriver->run();
}

/**
 * @brief Register有参测试1
 * 异常获取对象
 * 
 */
TEST(IocContainerTest, case8) {
    IocContainer ioc;
    ioc.RegisterNormal<BYDCar, const string&, const string&, const int&>("BYDCarDriver");
    
    shared_ptr<BYDCar> CarDriver = ioc.ResolveShared<BYDCar, const string&, const string&, const int&>("CarDriverNone", "myCar", "123412344", 26);
    CarDriver->run();
}
