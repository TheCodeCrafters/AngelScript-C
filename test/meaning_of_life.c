//
// Created by ENDERZOMBI102 on 20/03/2023.
//

#include "angelscript/angelscript_c.h"
#include <assert.h>

#include "stdio.h"

void messageCallback( const asSMessageInfo* msg, void* obj ) {
	printf( "Received message from VM: `%s`\n", msg->message );
	(void) obj;
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
	TRY(asEngine_SetMessageCallback( engine, (asFUNCTION_t*) messageCallback, NULL, asCALL_CDECL ));
	TRY(asEngine_RegisterGlobalFunction( engine, "void print(const int)", (asFUNCTION_t*) print, asCALL_CDECL, NULL ));

	// setup script
	asIScriptModule* module = asEngine_GetModule( engine, "app", asGM_ALWAYS_CREATE );
	TRY(asModule_AddScriptSection( module, "main.as", "int main() { print(42); return 0; }", 0, 0 ));
	TRY(asModule_Build( module ));

	// run script
	asIScriptContext* ctx = asEngine_CreateContext( engine );
	asIScriptFunction* func = asModule_GetFunctionByName( asEngine_GetModule( engine, "app", asGM_ONLY_IF_EXISTS ), "main" );
	TRY(asContext_Prepare( ctx, func ));
	r = asContext_Execute( ctx );

	int code = -1;
	if ( r == asEXECUTION_FINISHED ) {
		code = asContext_GetReturnWord( ctx );
		printf( "return value: %d", code );
	}

	// shutdown
	TRY(asContext_Release( ctx ));
	TRY(asEngine_ShutdownAndRelease( engine ));

	return code;
}


