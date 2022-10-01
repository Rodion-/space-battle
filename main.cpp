#include <iostream>
#include <cstring>
#include <math.h>
#include <vector>
#include <memory>
#include <assert.h>

#include <gtest/gtest.h>


typedef struct position
{
    int x;
    int y;
} position;

typedef struct velocity
{
    int x;
    int y;
} velocity;



class UObject   //
{

    position coordinates;
    velocity v;

    int angle;


    public:

    UObject(){}
    ~UObject(){}

    void set_property ( std::string property )
    {
    }

    void get_property ( std::string property )
    {
    }

};

class IMove
{
    virtual void set_position( position* ) = 0;
    virtual void get_position( position*  ) = 0;
    virtual void set_velocity( velocity*  ) = 0;
    virtual void get_velocity( velocity*  ) = 0;

    virtual void execute ( void ) = 0;

};

class IRotation
{
    virtual void set_angle( int  ) = 0;
    virtual void get_angle( int*  ) = 0;

    virtual void execute ( void ) = 0;
};


class MoveAdapter : IMove
{
    std::unique_ptr<UObject> ob;

    //----mock part
    position pos;
    velocity vel;
    //----

    public:

    MoveAdapter( std::unique_ptr<UObject> _ob ) : ob( std::move( _ob ) ) {}
    ~MoveAdapter(){}

    void execute(  void ) override
    {
        if( !pos.x && !pos.y ) throw -1;
        if( vel.x && !vel.y ) throw -1;
        if( !pos.x && !pos.y && vel.x && !vel.y ) throw -1;

        pos.x = pos.x + vel.x;
        pos.y = pos.y + vel.y;
    }

    void set_position( position* xy )  override
    {
        pos = *xy;
    }

    void get_position( position* xy ) override
    {
        xy->x = pos.x;
        xy->y = pos.y;
    }

    void set_velocity( velocity* v ) override
    {
        vel = *v;
    }

    void get_velocity( velocity* v ) override
    {
        v->x = vel.x;
        v->y = vel.y;
    }
};

class RotationAdapter : IRotation
{
    std::unique_ptr<UObject> ob;
    //---Mock
    int angle;
    //-------

    public:

    RotationAdapter( std::unique_ptr<UObject> _ob ) : ob( std::move( _ob ) ) {}
    ~RotationAdapter(){}

    void set_angle( int  a ) override
    {
        angle = a;
    }

    void get_angle( int* a ) override
    {
        *a = angle;
    }

    void execute() override
    {
        if( !angle ) throw -1;
    }

};

std::unique_ptr<UObject> spaceship;

MoveAdapter move_spaceship ( std::move(spaceship) );

RotationAdapter rotate_spaceship ( std::move(spaceship) );


//  Для объекта, находящегося в точке (12, 5) и движущегося со скоростью (-7, 3) движение меняет положение объекта на (5, 8)

TEST( test1, test)
{
    position spaceship_position{ 12 , 5 };
    velocity spaceship_velocity{ -7 , 3 };

    move_spaceship.set_position( &spaceship_position );
    move_spaceship.set_velocity( &spaceship_velocity );

    move_spaceship.execute();

    move_spaceship.get_position( &spaceship_position );

    EXPECT_EQ( spaceship_position.x , 5 );
    EXPECT_EQ( spaceship_position.y , 8 );

}

//  Попытка сдвинуть объект, у которого невозможно прочитать положение в пространстве, приводит к ошибке

TEST( test2 , test )
{
    using namespace std;

    position spaceship_position{ 0 , 0 };
    move_spaceship.set_position( &spaceship_position );

    EXPECT_ANY_THROW ( move_spaceship.execute(); );
}

//  Попытка сдвинуть объект, у которого невозможно прочитать значение мгновенной скорости, приводит к ошибке

TEST( test3 , test )
{
    using namespace std;

    velocity spaceship_velocity{ 0 , 0 };
    move_spaceship.set_velocity( &spaceship_velocity );

    EXPECT_ANY_THROW ( move_spaceship.execute(); );
}

//  Попытка сдвинуть объект, у которого невозможно изменить положение в пространстве, приводит к ошибке

TEST( test4 , test )
{
    using namespace std;

    position spaceship_position{ 0 , 0 };
    velocity spaceship_velocity{ 0 , 0 };

    move_spaceship.set_velocity( &spaceship_velocity );
    move_spaceship.set_position( &spaceship_position );

    EXPECT_ANY_THROW ( move_spaceship.execute(); );
}

//  Поворот на 90 градусов

TEST( test5 , test )
{
    using namespace std;

    int angle = 0;

    rotate_spaceship.set_angle( 90 );

    rotate_spaceship.execute();

    rotate_spaceship.get_angle( &angle );

    EXPECT_EQ ( angle , 90 );
}

//  Попытка сдвинуть объект, у которого невозможно изменить положение в пространстве, приводит к ошибке

TEST( test6 , test )
{
    using namespace std;

    rotate_spaceship.set_angle( 0 );

    EXPECT_ANY_THROW (  rotate_spaceship.execute(); );
}


int main ( int argc , char** argv )
{
    #if G_TEST_RUN
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    #endif

    using namespace std;
		
    try
    {
        cout<<"space battle"<<endl;


    }
    catch( ... )
    {
      cout<<"error : " <<endl;

    }

    return 0;
}
