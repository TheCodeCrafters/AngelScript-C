//
// Created by ENDERZOMBI102 on 20/03/2023.
//

#include "angelscript_c.h"
#include <assert.h>

#include "stdio.h"

void __stdcall messageCallback( const asSMessageInfo* msg, void* obj ) {
	printf( "Received message from VM: `%s`\n", msg->message );
}

void __stdcall print( const int input ) {
	printf( "Number is %d\n", input );
}

#define TRY( expr ) r = expr; assert( r >= 0 )

int main() {
	printf( "AngelScript v%s compiled with options `%s`\n", asGetLibraryVersion(), asGetLibraryOptions() );

	int r;
	asIScriptEngine* engine = asCreateScriptEngine( ANGELSCRIPT_VERSION );

	// setup engine
	TRY(asEngine_SetMessageCallback( engine, messageCallback, NULL, asCALL_STDCALL ));
	TRY(asEngine_RegisterGlobalFunction( engine, "void print(const int)", print, asCALL_STDCALL, NULL ));

	// setup script
	asIScriptModule* module = asEngine_GetModule( engine, "app", asGM_ALWAYS_CREATE );
	TRY(asModule_AddScriptSection( module, "main.as", "int main() { print(42); return 0; }", 0, 0 ));
	TRY(asModule_Build( module ));

	// run script
	asIScriptContext* ctx = asEngine_CreateContext( engine );
	asIScriptFunction* func = asModule_GetFunctionByName( asEngine_GetModule( engine, "app", asGM_ONLY_IF_EXISTS ), "main" );
	TRY(asContext_Prepare( ctx, func ));
	r = asContext_Execute( ctx );
	if ( r == asEXECUTION_FINISHED ) {
		printf( "return value: %lu", asContext_GetReturnDWord( ctx ) );
	}
	TRY(asContext_Release( ctx ));

	// shutdown
	TRY(asEngine_ShutdownAndRelease( engine ));
}


