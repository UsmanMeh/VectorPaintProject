#pragma once
#include <iostream>
#include <vector>

class ISubject;
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void Update(ISubject&) = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    void Attach(IObserver& o) { observers.push_back(&o); }
    void Detach(IObserver& o)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), &o));
    }
    void Notify()
    {
        for (auto* o : observers) {
            o->Update(*this);
        }
    }
private:
    std::vector<IObserver*> observers;
};