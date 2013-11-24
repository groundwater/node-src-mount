// http://linux.die.net/man/2/mount
#include <sys/mount.h>
#include <v8.h>
#include <node.h>

using namespace std;
using namespace v8;
using namespace node;

namespace NodeOS
{
  
  static Handle<Object> GetMountFlags() {
    HandleScope scope;
    
    Local<Object> flags = Object::New();
    
    flags->Set( String::New("MS_MGC_VAL"), Integer::New(MS_MGC_VAL) );
    flags->Set( String::New("MS_BIND"), Integer::New(MS_BIND) );
    flags->Set( String::New("MS_DIRSYNC"), Integer::New(MS_DIRSYNC) );
    flags->Set( String::New("MS_MANDLOCK"), Integer::New(MS_MANDLOCK) );
    flags->Set( String::New("MS_MOVE"), Integer::New(MS_MOVE) );
    flags->Set( String::New("MS_NOATIME"), Integer::New(MS_NOATIME) );
    flags->Set( String::New("MS_NODEV"), Integer::New(MS_NODEV) );
    flags->Set( String::New("MS_NODIRATIME"), Integer::New(MS_NODIRATIME) );
    flags->Set( String::New("MS_NOEXEC"), Integer::New(MS_NOEXEC) );
    flags->Set( String::New("MS_NOSUID"), Integer::New(MS_NOSUID) );
    flags->Set( String::New("MS_RDONLY"), Integer::New(MS_RDONLY) );
    flags->Set( String::New("MS_RELATIME"), Integer::New(MS_RELATIME) );
    flags->Set( String::New("MS_REMOUNT"), Integer::New(MS_REMOUNT) );
    flags->Set( String::New("MS_SILENT"), Integer::New(MS_SILENT) );
    flags->Set( String::New("MS_STRICTATIME"), Integer::New(MS_STRICTATIME) );
    flags->Set( String::New("MS_SYNCHRONOUS"), Integer::New(MS_SYNCHRONOUS) );
    
    return scope.Close(flags);
  }
  
  static Handle<Value> Mount(const Arguments& args) {
    HandleScope scope;
    
    // convert values from JS-land
    String::Utf8Value dev(args[0]);
    String::Utf8Value path(args[1]);
    String::Utf8Value type(args[2]);
    String::Utf8Value extras(args[4]);
    unsigned long flags = Local<Number>::Cast(args[3])->Value();
    
    // syscall
    int res = mount(*dev, *path, *type, flags, *extras);
    
    return scope.Close(Integer::New(res));
  }

  static void init(Handle<Object> target) {
    
    // set flags once only
    target->Set(String::NewSymbol("flags"), GetMountFlags());
    
    // mount wrapper
    target->Set(String::NewSymbol("mount"),
      FunctionTemplate::New(Mount)->GetFunction());
      
  }
}

NODE_MODULE(binding, NodeOS::init)
