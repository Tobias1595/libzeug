#include <functional>
#include <scriptzeug/Scriptable.h>
#include <scriptzeug/BackendJavaScript/JSScriptEnvironment.h>


namespace scriptzeug
{


using namespace v8;


static void testFunction(const v8::FunctionCallbackInfo<v8::Value> & args)
{
    printf("Test Function\n");
    return;

    /*
    for (int i=0; i<args.Length(); i++) {
        v8::HandleScope scope(args.GetIsolate());

        // String argument
//      v8::String::AsciiValue str(args[i]);
//      printf("%s\n", *str);

        // Int argument
        int num = args[i]->Int32Value();
        printf("%d\n", num);
    }
    */

    // Set return value
    /*
    v8::Handle<v8::String> source = ReadFile(args.GetIsolate(), *file);
    args.GetReturnValue().Set(source);
    */
}


JSScriptEnvironment::JSScriptEnvironment()
{
    // Get isolate
    Isolate * isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // Create global object
    Handle<ObjectTemplate> global = ObjectTemplate::New();

    // Create global context
    Handle<Context> context = Context::New(isolate, nullptr, global);
    m_context.Reset(isolate, context);
}

JSScriptEnvironment::~JSScriptEnvironment()
{
    // Destroy global context
    m_context.Dispose();
}

void JSScriptEnvironment::registerObject(const std::string & name, Scriptable * obj)
{
    // Get isolate
    Isolate * isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // Get global context
    Local<Context> context = Local<Context>::New(isolate, m_context);
    Context::Scope context_scope(context);

    // Create class template
    Handle<ObjectTemplate> templ = ObjectTemplate::New();
    templ->SetInternalFieldCount(1);

    // Register functions of the objects
    const std::vector<AbstractFunction *> & funcs = obj->functions();
    for (std::vector<AbstractFunction *>::const_iterator it = funcs.begin(); it != funcs.end(); ++it) {
        AbstractFunction * func = *it;

        templ->Set(String::New(func->name().c_str()), FunctionTemplate::New(testFunction));
    }

    // Make persistent template handle
    Persistent<ObjectTemplate> class_template;
    class_template.Reset(isolate, templ);

    // Create new object
    Handle<Object>   object  = templ->NewInstance();
    Handle<External> obj_ptr = External::New(obj);
    object->SetInternalField(0, obj_ptr);

    // Register object in global variables
    context->Global()->Set(String::New(name.c_str()), object, ReadOnly);
}

void JSScriptEnvironment::evaluate(const std::string & code)
{
    // Get isolate
    Isolate * isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // Get global context
    Local<Context> context = Local<Context>::New(isolate, m_context);
    Context::Scope context_scope(context);

    // Create and compile script
    Handle<String> source = String::New(code.c_str());
    Handle<Script> script = Script::Compile(source);

    // Run script
    Handle<Value> result = script->Run();

    // Print result
    String::AsciiValue ascii(result);
    printf("%s\n", *ascii);
}


} // namespace
