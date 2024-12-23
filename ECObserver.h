#ifndef ECOBSERVER_H
#define ECOBSERVER_H

#include <vector>
#include <algorithm>
#include <iostream>

class ECObserver
{
public:
    virtual ~ECObserver() {}
    virtual void Update() = 0;
};

class ECObserverSubject
{
public:
    ECObserverSubject() {}
    virtual ~ECObserverSubject() {}
    void Attach( ECObserver *pObs ){
    //std::cout << "Adding an observer.\n";
        listObservers.push_back(pObs);
    }
    void Detach( ECObserver *pObs ){
        listObservers.erase(std::remove(listObservers.begin(), listObservers.end(), pObs), listObservers.end());
    }
    void Notify()
    {
    //std::cout << "Notify: number of observer: " << listObservers.size() << std::endl;
        for(unsigned int i=0; i<listObservers.size(); ++i)
        {
            listObservers[i]->Update();
        }
    }
    
private:
    std::vector<ECObserver *> listObservers;
};

#endif
