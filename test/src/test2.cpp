//
// Created by ENDERZOMBI102 on 28/03/2023.
//

#include "angelscript.h"
#include <cassert>
#include <cstdio>

void messageCallback( const asSMessageInfo* msg, void* obj ) {
	printf( "Received message from VM: `%s`\n", msg->message );
}

void print( const int input ) {
	printf( "Number is %d\n", input );
}

#define TRY( expr ) r = expr; assert( r >= 0 )

int main() {
	printf( "AngelScript v%s compiled with options `%s`\n", asGetLibraryVersion(), asGetLibraryOptions() );

	int r;
	asIScriptEngine* engine = asCreateScriptEngine( ANGELSCRIPT_VERSION );

	// setup engine
	TRY( engine->SetMessageCallback( asFUNCTION( messageCallback ), nullptr, asECallConvTypes::asCALL_CDECL ) );
	TRY( engine->RegisterGlobalFunction( "void print(const int)", asFUNCTION( print ), asECallConvTypes::asCALL_CDECL ) );

	// setup script
	asIScriptModule* mod = engine->GetModule( "app", asGM_ALWAYS_CREATE );
	TRY( mod->AddScriptSection( "main.as", "int main() { print(42); return 0; }", 0, 0 ) );
	TRY( mod->Build() );

	// run script
	asIScriptContext* ctx = engine->CreateContext();
	asIScriptFunction* func = mod->GetFunctionByName( "main" );
	TRY( ctx->Prepare( func ) );
	r = ctx->Execute();
	if ( r == asEXECUTION_FINISHED )
		printf( "return value: %lu", ctx->GetReturnDWord() );

	TRY( ctx->Release() );

	// shutdown
	TRY( engine->ShutDownAndRelease() );
}
