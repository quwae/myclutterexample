#include <clutter/clutter.h>
#include <stdlib.h>

#define errlog g_error
#define dbglog g_debug

/*
  Wrapper for clutter_init()
  clutter_init()のラッパー関数

  log result of clutter_init()
  clutter_init()の結果を出力する。
*/
static ClutterInitError my_clutter_init( int argc, char *argv[] )
{
  ClutterInitError ret = clutter_init( &argc, &argv );
  switch( ret ) {
  case CLUTTER_INIT_SUCCESS:
    dbglog( "Initialisation successful\n" );
    break;
  case CLUTTER_INIT_ERROR_UNKNOWN:
    errlog( "Unknown error\n" );
    break;
  case CLUTTER_INIT_ERROR_THREADS:
    errlog( "Thread initialisation failed\n" );
    break;
  case CLUTTER_INIT_ERROR_BACKEND:
    errlog( "Backend initialisation failed\n" );
    break;
  case CLUTTER_INIT_ERROR_INTERNAL:
    errlog( "Internal error\n" );
    break;
  default:
    errlog( "Other error\n" );
    break;
  }
  return ret;
}

int main(int argc, char *argv[])
{
  ClutterInitError ret = my_clutter_init( argc, argv );
  if( ret != CLUTTER_INIT_SUCCESS ) {
    return EXIT_FAILURE;
  }

  ClutterColor stage_color = { 0, 0, 0, 255 };

  ClutterActor *stage = clutter_stage_new();
  if( stage == NULL ) {
    errlog( "clutter_stage_new() failed\n" );
    return EXIT_FAILURE;
  }

  clutter_actor_set_size( stage, 512, 512 );

  clutter_actor_set_background_color( stage, &stage_color );

  g_signal_connect( stage, "destroy", clutter_main_quit, NULL );

  clutter_actor_show( stage );

  clutter_main();

  return EXIT_SUCCESS;
}
