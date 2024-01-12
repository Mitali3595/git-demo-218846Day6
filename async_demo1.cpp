

/*
    A   B   C

    Option1:one after other.always complete one
        thing before starting next task

        *Name:single thread technique

    =====================================================================================

    option2:I will Complete all tasks in such a way
        that I "pratically start all of them at the same time "
        but keep jugling them based on some criteria

        *Name:multithread approach
    ======================================================================================
    option3:map no of tasks amongst among number of available "workers"

         *Name:parallel execution

    =====================================================================================
    option 4:start a task.Either deligate it to another worker or
        do it yourself after some time.

        If someone  else is doing the task monitor it wait for their
        work to be done,take followup actions accordingly

        starting step2 before conmpleting step1 but need to take update
        about another tasks also

         *Name:Asynchronus Execution
    =======================================================================================

*/

/*
    2 Tasks :
    calculate factorial of 5
    calculate Square of number given by user

    square will initiate but in same duration we will calculate factorial
*/

#include <iostream>
#include <future> //header for async code
#include <thread>

int square(std::future<int> &ft)
{
    std::this_thread::sleep_for(std::chrono::seconds(2)); // delay
    std::cout << "HEllo from Square.I have started my work!\n";

    //get value
    int number = ft.get();
    return number * number;   //no promise bcz give immediate value 
}

int factorial(int number)
{

    std::this_thread::sleep_for(std::chrono::seconds(3)); // dealy for real world another tasks
    if (number < 0)
    {
        throw std::runtime_error("negative number error! \n");
    }
    if (number == 0 || number == 1)
    {
        return 1;
    }
    else
    {
        return number * factorial(number - 1);
    }
}

int main()
{

    //step 1:Make a promise that will provide you parameter later and initiate task
    std::promise<int> pr;

    //step 2:A future linked to the promise
    std::future<int> ft = pr.get_future();

    /*
        OS:launch square (if possible as new thread)
        std::launch::async--launch policy 
        &square-target functionality
        std::ref(ft)--have future link to promise

    */
    std::future<int> result_ft = std::async(std::launch::async, &square, std::ref(ft));


    //fact will do work after 3 sec
    std::cout <<factorial(5)<<std::endl;



    int val=0;
    //val given by user
    //std::cout<<"enter value:"<<std::endl;
    std::cin>>val;
    //set value to promise set value -give signal
    pr.set_value(val);

    std::cout << " Result of Square is:" << result_ft.get();
}

// to run command:g++ async_demo1.cpp -lpthread -o app && ./app

/*
    client server architecture


    future promise model:way in which 2 tasks can talk yo each other

    main thread-fact cal and square in this case

    square calculation:main needs to delegate task of square calculation 

    --->new thread for square is register with OS




*/