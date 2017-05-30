#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Common/Multithreading/ThreadsBarrier.h"

#include "swGraphicAPI/ResourceManager/AsyncLoad/LoadBarrier.h"



const int numThreads = 4;

sw::ThreadsBarrier		gPreAccessBarrier( numThreads );
sw::ThreadsBarrier		gPreWaitBarrier( numThreads - 1 );
sw::LoadBarrier			gLoadBarrier;
std::vector< int >		gOrderChecker;
std::mutex				gCheckerLock;

filesystem::Path assetFile( "assets/wombat.jpg" );
filesystem::Path independentAsset( "assets/texture.jpg" );

bool threadsInternalResult[ numThreads ];
bool notNullWaitingAsset[ numThreads ];



// ================================ //
//
void		PushThreadNum		( int threadNum )
{
	gCheckerLock.lock();
	gOrderChecker.push_back( threadNum );
	gCheckerLock.unlock();
}


// ================================ //
//
void		FakeLoadAsset		( int threadNum )
{
	PushThreadNum( threadNum );

	gPreWaitBarrier.ArriveAndWait();

	std::this_thread::sleep_for( std::chrono::milliseconds( 13 ) );

	PushThreadNum( threadNum );

	gLoadBarrier.LoadingCompleted( assetFile );
}

// ================================ //
//
void		LoadingThread		( int threadNum )
{
	auto result = gLoadBarrier.RequestAsset( assetFile );

	// Allow other threads to call RequestAsset.
	gPreAccessBarrier.ArriveAndWait();
	
	threadsInternalResult[ threadNum ] = result.second;
	notNullWaitingAsset[ threadNum ] = result.first != nullptr;
	
	FakeLoadAsset( threadNum );
}

// ================================ //
//
void		RequestingThread	( int threadNum )
{
	// LoadingThread must RequestAsset first. Wait for it.
	gPreAccessBarrier.ArriveAndWait();

	auto result = gLoadBarrier.RequestAsset( assetFile );

	threadsInternalResult[ threadNum ] = result.second;
	notNullWaitingAsset[ threadNum ] = result.first != nullptr;

	gPreWaitBarrier.ArriveAndWait();
	gLoadBarrier.WaitUntilLoaded( result.first );
	
	PushThreadNum( threadNum );
}

// ================================ //
//
void		IndependentAssetThread	( int threadNum )
{
	// LoadingThread must RequestAsset first. Wait for it.
	gPreAccessBarrier.ArriveAndWait();

	auto result = gLoadBarrier.RequestAsset( independentAsset );

	// Independent thread should pass without blocking. result.second should be false.
	threadsInternalResult[ threadNum ] = result.second;
	notNullWaitingAsset[ threadNum ] = result.first != nullptr;
}


// ================================ //
// Only one thread should enter loading at the same time. Rest should wait.
TEST_CASE( "LoadBarrier" )
{
	std::thread threads[ numThreads ];

	threads[ 0 ] = std::thread( &LoadingThread, 0 );
	for( int i = 1; i < numThreads - 1; ++i )
		threads[ i ] = std::thread( &RequestingThread, i );

	// Independent thread
	threads[ numThreads - 1 ] = std::thread( &IndependentAssetThread, numThreads - 1 );

	for( auto& thread : threads )
		thread.join();


	// Waiting asset should never be nullptr.
	for( auto notNull : notNullWaitingAsset )
		CHECK( notNull == true );

	CHECK( threadsInternalResult[ 0 ] == false );
	CHECK( threadsInternalResult[ 1 ] == true );
	CHECK( threadsInternalResult[ 2 ] == true );
	CHECK( threadsInternalResult[ 3 ] == false );

	REQUIRE( gOrderChecker.size() == 4 );

	CHECK( gOrderChecker[ 0 ] == 0 );
	CHECK( gOrderChecker[ 1 ] == 0 );
	CHECK( ( gOrderChecker[ 2 ] == 1 || gOrderChecker[ 2 ] == 2 ) );
	CHECK( ( gOrderChecker[ 3 ] == 1 || gOrderChecker[ 3 ] == 2 ) );

}

