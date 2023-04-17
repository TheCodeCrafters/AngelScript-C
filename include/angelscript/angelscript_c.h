//
// Created by ENDERZOMBI102 on 19/03/2023.
//

#ifndef ANGELSCRIPT_C_H
	#define ANGELSCRIPT_C_H

	#include "stddef.h"

	#ifdef __cplusplus
		extern "C" {
	#endif

	// AngelScript version
	#define ANGELSCRIPT_VERSION 23600
	#define ANGELSCRIPT_VERSION_STRING "2.36.0"

	// region Enumerations

	// Return codes
	typedef enum {
		asSUCCESS = 0,
		asERROR = -1,
		asCONTEXT_ACTIVE = -2,
		asCONTEXT_NOT_FINISHED = -3,
		asCONTEXT_NOT_PREPARED = -4,
		asINVALID_ARG = -5,
		asNO_FUNCTION = -6,
		asNOT_SUPPORTED = -7,
		asINVALID_NAME = -8,
		asNAME_TAKEN = -9,
		asINVALID_DECLARATION = -10,
		asINVALID_OBJECT = -11,
		asINVALID_TYPE = -12,
		asALREADY_REGISTERED = -13,
		asMULTIPLE_FUNCTIONS = -14,
		asNO_MODULE = -15,
		asNO_GLOBAL_VAR = -16,
		asINVALID_CONFIGURATION = -17,
		asINVALID_INTERFACE = -18,
		asCANT_BIND_ALL_FUNCTIONS = -19,
		asLOWER_ARRAY_DIMENSION_NOT_REGISTERED = -20,
		asWRONG_CONFIG_GROUP = -21,
		asCONFIG_GROUP_IS_IN_USE = -22,
		asILLEGAL_BEHAVIOUR_FOR_TYPE = -23,
		asWRONG_CALLING_CONV = -24,
		asBUILD_IN_PROGRESS = -25,
		asINIT_GLOBAL_VARS_FAILED = -26,
		asOUT_OF_MEMORY = -27,
		asMODULE_IS_IN_USE = -28
	} asERetCodes;

	// Engine properties
	typedef enum {
		asEP_ALLOW_UNSAFE_REFERENCES = 1,
		asEP_OPTIMIZE_BYTECODE = 2,
		asEP_COPY_SCRIPT_SECTIONS = 3,
		asEP_MAX_STACK_SIZE = 4,
		asEP_USE_CHARACTER_LITERALS = 5,
		asEP_ALLOW_MULTILINE_STRINGS = 6,
		asEP_ALLOW_IMPLICIT_HANDLE_TYPES = 7,
		asEP_BUILD_WITHOUT_LINE_CUES = 8,
		asEP_INIT_GLOBAL_VARS_AFTER_BUILD = 9,
		asEP_REQUIRE_ENUM_SCOPE = 10,
		asEP_SCRIPT_SCANNER = 11,
		asEP_INCLUDE_JIT_INSTRUCTIONS = 12,
		asEP_STRING_ENCODING = 13,
		asEP_PROPERTY_ACCESSOR_MODE = 14,
		asEP_EXPAND_DEF_ARRAY_TO_TMPL = 15,
		asEP_AUTO_GARBAGE_COLLECT = 16,
		asEP_DISALLOW_GLOBAL_VARS = 17,
		asEP_ALWAYS_IMPL_DEFAULT_CONSTRUCT = 18,
		asEP_COMPILER_WARNINGS = 19,
		asEP_DISALLOW_VALUE_ASSIGN_FOR_REF_TYPE = 20,
		asEP_ALTER_SYNTAX_NAMED_ARGS = 21,
		asEP_DISABLE_INTEGER_DIVISION = 22,
		asEP_DISALLOW_EMPTY_LIST_ELEMENTS = 23,
		asEP_PRIVATE_PROP_AS_PROTECTED = 24,
		asEP_ALLOW_UNICODE_IDENTIFIERS = 25,
		asEP_HEREDOC_TRIM_MODE = 26,
		asEP_MAX_NESTED_CALLS = 27,
		asEP_GENERIC_CALL_MODE = 28,
		asEP_INIT_STACK_SIZE = 29,
		asEP_INIT_CALL_STACK_SIZE = 30,
		asEP_MAX_CALL_STACK_SIZE = 31,
		asEP_IGNORE_DUPLICATE_SHARED_INTF = 32,
		asEP_NO_DEBUG_OUTPUT = 33,

		asEP_LAST_PROPERTY
	} asEEngineProp;

	// Calling conventions
	typedef enum {
		asCALL_CDECL = 0,
		asCALL_STDCALL = 1,
		asCALL_THISCALL_ASGLOBAL = 2,
		asCALL_THISCALL = 3,
		asCALL_CDECL_OBJLAST = 4,
		asCALL_CDECL_OBJFIRST = 5,
		asCALL_GENERIC = 6,
		asCALL_THISCALL_OBJLAST = 7,
		asCALL_THISCALL_OBJFIRST = 8
	} asECallConvTypes;

	// Object type flags
	typedef enum {
		asOBJ_REF = ( 1 << 0 ),
		asOBJ_VALUE = ( 1 << 1 ),
		asOBJ_GC = ( 1 << 2 ),
		asOBJ_POD = ( 1 << 3 ),
		asOBJ_NOHANDLE = ( 1 << 4 ),
		asOBJ_SCOPED = ( 1 << 5 ),
		asOBJ_TEMPLATE = ( 1 << 6 ),
		asOBJ_ASHANDLE = ( 1 << 7 ),
		asOBJ_APP_CLASS = ( 1 << 8 ),
		asOBJ_APP_CLASS_CONSTRUCTOR = ( 1 << 9 ),
		asOBJ_APP_CLASS_DESTRUCTOR = ( 1 << 10 ),
		asOBJ_APP_CLASS_ASSIGNMENT = ( 1 << 11 ),
		asOBJ_APP_CLASS_COPY_CONSTRUCTOR = ( 1 << 12 ),
		asOBJ_APP_CLASS_C = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_CONSTRUCTOR ),
		asOBJ_APP_CLASS_CD = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_CONSTRUCTOR + asOBJ_APP_CLASS_DESTRUCTOR ),
		asOBJ_APP_CLASS_CA = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_CONSTRUCTOR + asOBJ_APP_CLASS_ASSIGNMENT ),
		asOBJ_APP_CLASS_CK = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_CONSTRUCTOR + asOBJ_APP_CLASS_COPY_CONSTRUCTOR ),
		asOBJ_APP_CLASS_CDA = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_CONSTRUCTOR + asOBJ_APP_CLASS_DESTRUCTOR +
								asOBJ_APP_CLASS_ASSIGNMENT ),
		asOBJ_APP_CLASS_CDK = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_CONSTRUCTOR + asOBJ_APP_CLASS_DESTRUCTOR +
								asOBJ_APP_CLASS_COPY_CONSTRUCTOR ),
		asOBJ_APP_CLASS_CAK = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_CONSTRUCTOR + asOBJ_APP_CLASS_ASSIGNMENT +
								asOBJ_APP_CLASS_COPY_CONSTRUCTOR ),
		asOBJ_APP_CLASS_CDAK = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_CONSTRUCTOR + asOBJ_APP_CLASS_DESTRUCTOR +
								 asOBJ_APP_CLASS_ASSIGNMENT + asOBJ_APP_CLASS_COPY_CONSTRUCTOR ),
		asOBJ_APP_CLASS_D = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_DESTRUCTOR ),
		asOBJ_APP_CLASS_DA = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_DESTRUCTOR + asOBJ_APP_CLASS_ASSIGNMENT ),
		asOBJ_APP_CLASS_DK = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_DESTRUCTOR + asOBJ_APP_CLASS_COPY_CONSTRUCTOR ),
		asOBJ_APP_CLASS_DAK = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_DESTRUCTOR + asOBJ_APP_CLASS_ASSIGNMENT +
								asOBJ_APP_CLASS_COPY_CONSTRUCTOR ),
		asOBJ_APP_CLASS_A = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_ASSIGNMENT ),
		asOBJ_APP_CLASS_AK = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_ASSIGNMENT + asOBJ_APP_CLASS_COPY_CONSTRUCTOR ),
		asOBJ_APP_CLASS_K = ( asOBJ_APP_CLASS + asOBJ_APP_CLASS_COPY_CONSTRUCTOR ),
		asOBJ_APP_CLASS_MORE_CONSTRUCTORS = ( 1 << 31 ),
		asOBJ_APP_PRIMITIVE = ( 1 << 13 ),
		asOBJ_APP_FLOAT = ( 1 << 14 ),
		asOBJ_APP_ARRAY = ( 1 << 15 ),
		asOBJ_APP_CLASS_ALLINTS = ( 1 << 16 ),
		asOBJ_APP_CLASS_ALLFLOATS = ( 1 << 17 ),
		asOBJ_NOCOUNT = ( 1 << 18 ),
		asOBJ_APP_CLASS_ALIGN8 = ( 1 << 19 ),
		asOBJ_IMPLICIT_HANDLE = ( 1 << 20 ),
		asOBJ_MASK_VALID_FLAGS = 0x801FFFFF,  // NOLINT(cppcoreguidelines-narrowing-conversions)
		// Internal flags
		asOBJ_SCRIPT_OBJECT = ( 1 << 21 ),
		asOBJ_SHARED = ( 1 << 22 ),
		asOBJ_NOINHERIT = ( 1 << 23 ),
		asOBJ_FUNCDEF = ( 1 << 24 ),
		asOBJ_LIST_PATTERN = ( 1 << 25 ),
		asOBJ_ENUM = ( 1 << 26 ),
		asOBJ_TEMPLATE_SUBTYPE = ( 1 << 27 ),
		asOBJ_TYPEDEF = ( 1 << 28 ),
		asOBJ_ABSTRACT = ( 1 << 29 ),
		asOBJ_APP_ALIGN16 = ( 1 << 30 )
	} asEObjTypeFlags;

	// Behaviours
	typedef enum {
		// Value object memory management
		asBEHAVE_CONSTRUCT,
		asBEHAVE_LIST_CONSTRUCT,
		asBEHAVE_DESTRUCT,

		// Reference object memory management
		asBEHAVE_FACTORY,
		asBEHAVE_LIST_FACTORY,
		asBEHAVE_ADDREF,
		asBEHAVE_RELEASE,
		asBEHAVE_GET_WEAKREF_FLAG,

		// Object operators
		asBEHAVE_TEMPLATE_CALLBACK,

		// Garbage collection behaviours
		asBEHAVE_FIRST_GC,
		asBEHAVE_GETREFCOUNT = asBEHAVE_FIRST_GC,
		asBEHAVE_SETGCFLAG,
		asBEHAVE_GETGCFLAG,
		asBEHAVE_ENUMREFS,
		asBEHAVE_RELEASEREFS,
		asBEHAVE_LAST_GC = asBEHAVE_RELEASEREFS,

		asBEHAVE_MAX
	} asEBehaviours;

	// Context states
	typedef enum {
		asEXECUTION_FINISHED = 0,
		asEXECUTION_SUSPENDED = 1,
		asEXECUTION_ABORTED = 2,
		asEXECUTION_EXCEPTION = 3,
		asEXECUTION_PREPARED = 4,
		asEXECUTION_UNINITIALIZED = 5,
		asEXECUTION_ACTIVE = 6,
		asEXECUTION_ERROR = 7,
		asEXECUTION_DESERIALIZATION = 8
	} asEContextState;

	// Message types
	typedef enum {
		asMSGTYPE_ERROR = 0,
		asMSGTYPE_WARNING = 1,
		asMSGTYPE_INFORMATION = 2
	} asEMsgType;

	// Garbage collector flags
	typedef enum {
		asGC_FULL_CYCLE = 1,
		asGC_ONE_STEP = 2,
		asGC_DESTROY_GARBAGE = 4,
		asGC_DETECT_GARBAGE = 8
	} asEGCFlags;

	// Token classes
	typedef enum {
		asTC_UNKNOWN = 0,
		asTC_KEYWORD = 1,
		asTC_VALUE = 2,
		asTC_IDENTIFIER = 3,
		asTC_COMMENT = 4,
		asTC_WHITESPACE = 5
	} asETokenClass;

	// Type id flags
	typedef enum {
		asTYPEID_VOID = 0,
		asTYPEID_BOOL = 1,
		asTYPEID_INT8 = 2,
		asTYPEID_INT16 = 3,
		asTYPEID_INT32 = 4,
		asTYPEID_INT64 = 5,
		asTYPEID_UINT8 = 6,
		asTYPEID_UINT16 = 7,
		asTYPEID_UINT32 = 8,
		asTYPEID_UINT64 = 9,
		asTYPEID_FLOAT = 10,
		asTYPEID_DOUBLE = 11,
		asTYPEID_OBJHANDLE = 0x40000000,
		asTYPEID_HANDLETOCONST = 0x20000000,
		asTYPEID_MASK_OBJECT = 0x1C000000,
		asTYPEID_APPOBJECT = 0x04000000,
		asTYPEID_SCRIPTOBJECT = 0x08000000,
		asTYPEID_TEMPLATE = 0x10000000,
		asTYPEID_MASK_SEQNBR = 0x03FFFFFF
	} asETypeIdFlags;

	// Type modifiers
	typedef enum {
		asTM_NONE = 0,
		asTM_INREF = 1,
		asTM_OUTREF = 2,
		asTM_INOUTREF = 3,
		asTM_CONST = 4
	} asETypeModifiers;

	// GetModule flags
	typedef enum {
		asGM_ONLY_IF_EXISTS = 0,
		asGM_CREATE_IF_NOT_EXISTS = 1,
		asGM_ALWAYS_CREATE = 2
	} asEGMFlags;

	// Compile flags
	typedef enum {
		asCOMP_ADD_TO_MODULE = 1
	} asECompileFlags;

	// Function types
	typedef enum {
		asFUNC_DUMMY = -1,
		asFUNC_SYSTEM = 0,
		asFUNC_SCRIPT = 1,
		asFUNC_INTERFACE = 2,
		asFUNC_VIRTUAL = 3,
		asFUNC_FUNCDEF = 4,
		asFUNC_IMPORTED = 5,
		asFUNC_DELEGATE = 6
	} asEFuncType;

	typedef enum asBOOL { asTRUE = 1, asFALSE = 0 } asBOOL_t;
	// endregion

	// region Data types
	struct asSVMRegisters;
	typedef struct asIScriptEngine asIScriptEngine;
	typedef struct asIScriptModule asIScriptModule;
	typedef struct asIScriptContext asIScriptContext;
	typedef struct asIScriptGeneric asIScriptGeneric;
	typedef struct asIScriptObject asIScriptObject;
	typedef struct asITypeInfo asITypeInfo;
	typedef struct asIScriptFunction asIScriptFunction;
	typedef struct asIJITCompiler asIJITCompiler;
	typedef struct asIThreadManager asIThreadManager;
	typedef struct asILockableSharedBool asILockableSharedBool;

	//
	// asBYTE  =  8 bits
	// asWORD  = 16 bits
	// asDWORD = 32 bits
	// asQWORD = 64 bits
	// asPWORD = size of a pointer
	//
	typedef signed char asINT8;
	typedef signed short asINT16;
	typedef signed int asINT32;
	typedef unsigned char asBYTE;
	typedef unsigned short asWORD;
	typedef unsigned int asUINT;
	typedef unsigned char asBYTE;
	typedef unsigned short asWORD;
	typedef unsigned int asUINT;
	typedef size_t asPWORD;
	#ifdef __LP64__
		typedef unsigned int  asDWORD;
		typedef unsigned long asQWORD;
		typedef long asINT64;
	#else
		typedef unsigned long asDWORD;
		#if defined(__GNUC__) || defined(__MWERKS__)
			typedef unsigned long long asQWORD;
			typedef long long asINT64;
		#else
		typedef unsigned __int64 asQWORD;
		typedef __int64 asINT64;
		#endif
	#endif

	typedef void ( *asFUNCTION_t )();
	typedef void ( *asGENFUNC_t )( asIScriptGeneric* );
	typedef void* ( *asALLOCFUNC_t )( size_t );
	typedef void ( *asFREEFUNC_t )( void* );
	typedef void ( *asCLEANENGINEFUNC_t )( asIScriptEngine* );
	typedef void ( *asCLEANMODULEFUNC_t )( asIScriptModule* );
	typedef void ( *asCLEANCONTEXTFUNC_t )( asIScriptContext* );
	typedef void ( *asCLEANFUNCTIONFUNC_t )( asIScriptFunction* );
	typedef void ( *asCLEANTYPEINFOFUNC_t )( asITypeInfo* );
	typedef void ( *asCLEANSCRIPTOBJECTFUNC_t )( asIScriptObject* );
	typedef asIScriptContext* ( *asREQUESTCONTEXTFUNC_t )( asIScriptEngine*, void* );
	typedef void ( *asRETURNCONTEXTFUNC_t )( asIScriptEngine*, asIScriptContext*, void* );
	typedef void ( *asCIRCULARREFFUNC_t )( asITypeInfo*, const void*, void* );
	typedef void (*asJITFunction)( struct asSVMRegisters *registers, asPWORD jitArg );
	// endregion Data typess

	// ANGELSCRIPT_EXPORT is defined when compiling the dll or lib
	// ANGELSCRIPT_DLL_LIBRARY_IMPORT is defined when dynamically linking to the dll through the link lib automatically generated by MSVC++
	// ANGELSCRIPT_DLL_MANUAL_IMPORT is defined when manually loading the dll
	// Don't define anything when linking statically to the lib

	#if defined( WIN32 ) || defined( _WIN32 ) || defined( __CYGWIN__ )
		#if defined( ANGELSCRIPT_EXPORT )
			#define AS_API __declspec( dllexport )
		#elif defined( ANGELSCRIPT_DLL_LIBRARY_IMPORT )
			#define AS_API __declspec( dllimport )
		#else  // statically linked library
			#define AS_API
		#endif
	#elif defined( __GNUC__ )
		#if defined( ANGELSCRIPT_EXPORT )
			#define AS_API __attribute__( ( visibility( "default" ) ) )
		#else
			#define AS_API
		#endif
	#else
		#define AS_API
	#endif

	// region Compatibility structures

	typedef struct {
		asDWORD          *programPointer;     // points to current bytecode instruction
		asDWORD          *stackFramePointer;  // function stack frame
		asDWORD          *stackPointer;       // top of stack (grows downward)
		asQWORD           valueRegister;      // temp register for primitives
		void             *objectRegister;     // temp register for objects and handles
		asITypeInfo      *objectType;         // type of object held in object register
		asBOOL_t          doProcessSuspend;   // whether or not the JIT should break out when it encounters a suspend instruction
		asIScriptContext *ctx;                // the active context
	} asSVMRegisters;

	typedef struct {
		const char* section;
		int row;
		int col;
		asEMsgType type;
		const char* message;
	} asSMessageInfo;

	typedef struct {
		const void* ( *getStringConstant )( const char* data, asUINT length, void* user );
		int ( *releaseStringConstant )( const void* str, void* user );
		int ( *getRawStringData )( const void* str, char* data, asUINT* length, void* user );
		void* user;
	} asStringFactory;

	typedef struct {
		int ( *read )( void* ptr, asUINT size, void* user );
		int ( *write )( const void* ptr, asUINT size, void* user );
		void* user;
	} asBinaryStream;

	typedef struct {
		int ( *compileFunction )( asIScriptFunction* function, asJITFunction* output, void* user );
		int ( *releaseJITFunction )( asJITFunction func, void* user );
		void* user;
	} asJITCompiler;

	typedef struct { void* user; } asThreadManager;
	// endregion

	// region API functions
	// Engine
	AS_API asIScriptEngine* asCreateScriptEngine( asDWORD version );
	AS_API const char* asGetLibraryVersion();
	AS_API const char* asGetLibraryOptions();

	// Context
	AS_API asIScriptContext* asGetActiveContext();

	// Thread support
	AS_API int asPrepareMultithread( asIThreadManager* externalMgr );
	AS_API void asUnprepareMultithread();
	AS_API asIThreadManager* asGetThreadManager();
	AS_API void asAcquireExclusiveLock();
	AS_API void asReleaseExclusiveLock();
	AS_API void asAcquireSharedLock();
	AS_API void asReleaseSharedLock();
	AS_API int asAtomicInc( int* value );
	AS_API int asAtomicDec( int* value );
	AS_API int asThreadCleanup();

	// Memory management
	AS_API int asSetGlobalMemoryFunctions( asALLOCFUNC_t allocFunc, asFREEFUNC_t freeFunc );
	AS_API int asResetGlobalMemoryFunctions();
	AS_API void* asAllocMem( size_t size );
	AS_API void asFreeMem( void* mem );

	// Auxiliary
	AS_API asILockableSharedBool* asCreateLockableSharedBool();
	// endregion API functions

	// region Interface declarations - engine
	// Memory management
	AS_API int asEngine_AddRef( asIScriptEngine* engine );
	AS_API int asEngine_Release( asIScriptEngine* engine );
	AS_API int asEngine_ShutdownAndRelease( asIScriptEngine* engine );

	// Engine properties
	AS_API int asEngine_SetEngineProperty( asIScriptEngine* engine, asEEngineProp property, asPWORD value );
	AS_API asPWORD asEngine_GetEngineProperty( asIScriptEngine* engine, asEEngineProp property );

	// Compiler messages
	AS_API int asEngine_SetMessageCallback( asIScriptEngine* engine, asFUNCTION_t* callback, void* obj, asDWORD callConv );
	AS_API int asEngine_ClearMessageCallback( asIScriptEngine* engine );
	AS_API int asEngine_WriteMessage( asIScriptEngine* engine, char* section, int row, int col, asEMsgType type, char* message );

	// JIT Compiler
	AS_API int asEngine_SetJITCompiler( asIScriptEngine* engine, asIJITCompiler* compiler );
	AS_API asIJITCompiler* asEngine_GetJITCompiler( asIScriptEngine* engine );

	// Global functions
	AS_API int asEngine_RegisterGlobalFunction( asIScriptEngine* engine, char* declaration, asFUNCTION_t* funcPointer, asDWORD callConv, void* auxiliary );
	AS_API asUINT asEngine_GetGlobalFunctionCount( asIScriptEngine* engine );
	AS_API asIScriptFunction* asEngine_GetGlobalFunctionByIndex( asIScriptEngine* engine, asUINT index );
	AS_API asIScriptFunction* asEngine_GetGlobalFunctionByDecl( asIScriptEngine* engine, char* declaration );

	// Global properties
	AS_API int asEngine_RegisterGlobalProperty( asIScriptEngine* engine, const char* declaration, void* pointer );
	AS_API asUINT asEngine_GetGlobalPropertyCount( asIScriptEngine* engine );
	AS_API int asEngine_GetGlobalPropertyByIndex( asIScriptEngine* engine, asUINT index, const char** name, const char** nameSpace, int* typeId, asBOOL_t* isConst, const char** configGroup, void** pointer, asDWORD* accessMask );
	AS_API int asEngine_GetGlobalPropertyIndexByName( asIScriptEngine* engine, const char* name );
	AS_API int asEngine_GetGlobalPropertyIndexByDecl( asIScriptEngine* engine, const char* decl );

	// Object types
	AS_API int asEngine_RegisterObjectType( asIScriptEngine* engine, const char* obj, int byteSize, asDWORD flags );
	AS_API int asEngine_RegisterObjectProperty( asIScriptEngine* engine, const char* obj, const char* declaration, int byteOffset, int compositeOffset, asBOOL_t isCompositeIndirect );
	AS_API int asEngine_RegisterObjectMethod( asIScriptEngine* engine, const char* obj, const char* declaration, asFUNCTION_t* funcPointer, asDWORD callConv, void* auxiliary, int compositeOffset, asBOOL_t isCompositeIndirect );
	AS_API int asEngine_RegisterObjectBehaviour( asIScriptEngine* engine, const char* obj, asEBehaviours behaviour, const char* declaration, asFUNCTION_t* funcPointer, asDWORD callConv, void* auxiliary, int compositeOffset, asBOOL_t isCompositeIndirect );
	AS_API int asEngine_RegisterInterface( asIScriptEngine* engine, const char* name );
	AS_API int asEngine_RegisterInterfaceMethod( asIScriptEngine* engine, const char* intf, const char* declaration );
	AS_API asUINT asEngine_GetObjectTypeCount( asIScriptEngine* engine );
	AS_API asITypeInfo* asEngine_GetObjectTypeByIndex( asIScriptEngine* engine, asUINT index );

	// String factory
	AS_API int asEngine_RegisterStringFactory( asIScriptEngine* engine, const char* datatype, asStringFactory* factory );
	AS_API int asEngine_GetStringFactoryReturnTypeId( asIScriptEngine* engine, asDWORD* flags );

	// Default array type
	AS_API int asEngine_RegisterDefaultArrayType( asIScriptEngine* engine, const char* type );
	AS_API int asEngine_GetDefaultArrayTypeId( asIScriptEngine* engine );

	// Enums
	AS_API int asEngine_RegisterEnum( asIScriptEngine* engine, const char* type );
	AS_API int asEngine_RegisterEnumValue( asIScriptEngine* engine, const char* type, const char* name, int value );
	AS_API asUINT asEngine_GetEnumCount( asIScriptEngine* engine );
	AS_API asITypeInfo* asEngine_GetEnumByIndex( asIScriptEngine* engine, asUINT index );

	// Funcdefs
	AS_API int asEngine_RegisterFuncdef( asIScriptEngine* engine, const char* decl );
	AS_API asUINT asEngine_GetFuncdefCount( asIScriptEngine* engine );
	AS_API asITypeInfo* asEngine_GetFuncdefByIndex( asIScriptEngine* engine, asUINT index );

	// Typedefs
	AS_API int asEngine_RegisterTypedef( asIScriptEngine* engine, const char* type, const char* decl );
	AS_API asUINT asEngine_GetTypedefCount( asIScriptEngine* engine );
	AS_API asITypeInfo* asEngine_GetTypedefByIndex( asIScriptEngine* engine, asUINT index );

	// Configuration groups
	AS_API int asEngine_BeginConfigGroup( asIScriptEngine* engine, const char* groupName );
	AS_API int asEngine_EndConfigGroup( asIScriptEngine* engine );
	AS_API int asEngine_RemoveConfigGroup( asIScriptEngine* engine, const char* groupName );
	AS_API asDWORD asEngine_SetDefaultAccessMask( asIScriptEngine* engine, asDWORD defaultMask );
	AS_API int asEngine_SetDefaultNamespace( asIScriptEngine* engine, const char* nameSpace );
	AS_API const char* asEngine_GetDefaultNamespace( asIScriptEngine* engine );

	// Script modules
	AS_API asIScriptModule* asEngine_GetModule( asIScriptEngine* engine, const char* module, asEGMFlags flag );
	AS_API int asEngine_DiscardModule( asIScriptEngine* engine, const char* module );
	AS_API asUINT asEngine_GetModuleCount( asIScriptEngine* engine );
	AS_API asIScriptModule* asEngine_GetModuleByIndex( asIScriptEngine* engine, asUINT index );

	// Script functions
	AS_API asIScriptFunction* asEngine_GetFunctionById( asIScriptEngine* engine, int funcId );

	// Type identification
	AS_API int asEngine_GetTypeIdByDecl( asIScriptEngine* engine, const char* decl );
	AS_API const char* asEngine_GetTypeDeclaration( asIScriptEngine* engine, int typeId, asBOOL_t includeNamespace );
	AS_API int asEngine_GetSizeOfPrimitiveType( asIScriptEngine* engine, int typeId );
	AS_API asITypeInfo* asEngine_GetTypeInfoById( asIScriptEngine* engine, int typeId );
	AS_API asITypeInfo* asEngine_GetTypeInfoByName( asIScriptEngine* engine, const char* name );
	AS_API asITypeInfo* asEngine_GetTypeInfoByDecl( asIScriptEngine* engine, const char* decl );

	// Script execution
	AS_API asIScriptContext* asEngine_CreateContext( asIScriptEngine* engine );
	AS_API void* asEngine_CreateScriptObject( asIScriptEngine* engine, const asITypeInfo* type );
	AS_API void* asEngine_CreateScriptObjectCopy( asIScriptEngine* engine, void* obj, const asITypeInfo* type );
	AS_API void* asEngine_CreateUninitializedScriptObject( asIScriptEngine* engine, const asITypeInfo* type );
	AS_API asIScriptFunction* asEngine_CreateDelegate( asIScriptEngine* engine, asIScriptFunction* func, void* obj );
	AS_API int asEngine_AssignScriptObject( asIScriptEngine* engine, void* dstObj, void* srcObj, const asITypeInfo* type );
	AS_API void asEngine_ReleaseScriptObject( asIScriptEngine* engine, void* obj, const asITypeInfo* type );
	AS_API void asEngine_AddRefScriptObject( asIScriptEngine* engine, void* obj, const asITypeInfo* type );
	AS_API int asEngine_RefCastObject( asIScriptEngine* engine, void* obj, asITypeInfo* fromType, asITypeInfo* toType, void** newPtr, asBOOL_t useOnlyImplicitCast );
	AS_API asILockableSharedBool* asEngine_GetWeakRefFlagOfScriptObject( asIScriptEngine* engine, void* obj, const asITypeInfo* type );

	// Context pooling
	AS_API asIScriptContext* asEngine_RequestContext( asIScriptEngine* engine );
	AS_API void asEngine_ReturnContext( asIScriptEngine* engine, asIScriptContext* ctx );
	AS_API int asEngine_SetContextCallbacks( asIScriptEngine* engine, asREQUESTCONTEXTFUNC_t requestCtx, asRETURNCONTEXTFUNC_t returnCtx, void* param );

	// String interpretation
	AS_API asETokenClass asEngine_ParseToken( asIScriptEngine* engine, const char* string, size_t stringLength, asUINT* tokenLength );

	// Garbage collection
	AS_API int asEngine_GarbageCollect( asIScriptEngine* engine, asDWORD flags, asUINT numIterations );
	AS_API void asEngine_GetGCStatistics( asIScriptEngine* engine, asUINT* currentSize, asUINT* totalDestroyed, asUINT* totalDetected, asUINT* newObjects, asUINT* totalNewDestroyed );
	AS_API int asEngine_NotifyGarbageCollectorOfNewObject( asIScriptEngine* engine, void* obj, asITypeInfo* type );
	AS_API int asEngine_GetObjectInGC( asIScriptEngine* engine, asUINT idx, asUINT* seqNbr, void** obj, asITypeInfo** type );
	AS_API void asEngine_GCEnumCallback( asIScriptEngine* engine, void* reference );
	AS_API void asEngine_ForwardGCEnumReferences( asIScriptEngine* engine, void* ref, asITypeInfo* type );
	AS_API void asEngine_ForwardGCReleaseReferences( asIScriptEngine* engine, void* ref, asITypeInfo* type );
	AS_API void asEngine_SetCircularRefDetectedCallback( asIScriptEngine* engine, asCIRCULARREFFUNC_t callback, void* param );

	// User data
	AS_API void* asEngine_SetUserData( asIScriptEngine* engine, void* data, asPWORD type );
	AS_API void* asEngine_GetUserData( asIScriptEngine* engine, asPWORD type );
	AS_API void asEngine_SetEngineUserDataCleanupCallback( asIScriptEngine* engine, asCLEANENGINEFUNC_t callback, asPWORD type );
	AS_API void asEngine_SetModuleUserDataCleanupCallback( asIScriptEngine* engine, asCLEANMODULEFUNC_t callback, asPWORD type );
	AS_API void asEngine_SetContextUserDataCleanupCallback( asIScriptEngine* engine, asCLEANCONTEXTFUNC_t callback, asPWORD type );
	AS_API void asEngine_SetFunctionUserDataCleanupCallback( asIScriptEngine* engine, asCLEANFUNCTIONFUNC_t callback, asPWORD type );
	AS_API void asEngine_SetTypeInfoUserDataCleanupCallback( asIScriptEngine* engine, asCLEANTYPEINFOFUNC_t callback, asPWORD type );
	AS_API void asEngine_SetScriptObjectUserDataCleanupCallback( asIScriptEngine* engine, asCLEANSCRIPTOBJECTFUNC_t callback, asPWORD type );

	// Exception handling
	AS_API int asEngine_SetTranslateAppExceptionCallback( asIScriptEngine* engine, asFUNCTION_t callback, void* param, int callConv );
	// endregion Interface declarations - engine

	// region Interface declarations - module
	AS_API asIScriptEngine* asModule_GetEngine( asIScriptModule* module );
	AS_API void asModule_SetName( asIScriptModule* module, const char* name );
	AS_API const char* asModule_GetName( asIScriptModule* module );
	AS_API void asModule_Discard( asIScriptModule* module );

	// Compilation
	AS_API int asModule_AddScriptSection( asIScriptModule* module, const char* name, const char* code, size_t codeLength, int lineOffset );
	AS_API int asModule_Build( asIScriptModule* module );
	AS_API int asModule_CompileFunction( asIScriptModule* module, const char* sectionName, const char* code, int lineOffset, asDWORD compileFlags, asIScriptFunction** outFunc );
	AS_API int asModule_CompileGlobalVar( asIScriptModule* module, const char* sectionName, const char* code, int lineOffset );
	AS_API asDWORD asModule_SetAccessMask( asIScriptModule* module, asDWORD accessMask );
	AS_API int asModule_SetDefaultNamespace( asIScriptModule* module, const char* nameSpace );
	AS_API const char* asModule_GetDefaultNamespace( asIScriptModule* module );

	// Functions
	AS_API asUINT asModule_GetFunctionCount( asIScriptModule* module );
	AS_API asIScriptFunction* asModule_GetFunctionByIndex( asIScriptModule* module, asUINT index );
	AS_API asIScriptFunction* asModule_GetFunctionByDecl( asIScriptModule* module, const char* decl );
	AS_API asIScriptFunction* asModule_GetFunctionByName( asIScriptModule* module, const char* name );
	AS_API int asModule_RemoveFunction( asIScriptModule* module, asIScriptFunction* func );

	// Global variables
	AS_API int asModule_ResetGlobalVars( asIScriptModule* module, asIScriptContext* ctx );
	AS_API asUINT asModule_GetGlobalVarCount( asIScriptModule* module );
	AS_API int asModule_GetGlobalVarIndexByName( asIScriptModule* module, const char* name );
	AS_API int asModule_GetGlobalVarIndexByDecl( asIScriptModule* module, const char* decl );
	AS_API const char* asModule_GetGlobalVarDeclaration( asIScriptModule* module, asUINT index, asBOOL_t includeNamespace );
	AS_API int asModule_GetGlobalVar( asIScriptModule* module, asUINT index, const char** name, const char** nameSpace, int* typeId, asBOOL_t* isConst );
	AS_API void* asModule_GetAddressOfGlobalVar( asIScriptModule* module, asUINT index );
	AS_API int asModule_RemoveGlobalVar( asIScriptModule* module, asUINT index );

	// Type identification
	AS_API asUINT asModule_GetObjectTypeCount( asIScriptModule* module );
	AS_API asITypeInfo* asModule_GetObjectTypeByIndex( asIScriptModule* module, asUINT index );
	AS_API int asModule_GetTypeIdByDecl( asIScriptModule* module, const char* decl );
	AS_API asITypeInfo* asModule_GetTypeInfoByName( asIScriptModule* module, const char* name );
	AS_API asITypeInfo* asModule_GetTypeInfoByDecl( asIScriptModule* module, const char* decl );

	// Enums
	AS_API asUINT asModule_GetEnumCount( asIScriptModule* module );
	AS_API asITypeInfo* asModule_GetEnumByIndex( asIScriptModule* module, asUINT index );

	// Typedefs
	AS_API asUINT asModule_GetTypedefCount( asIScriptModule* module );
	AS_API asITypeInfo* asModule_GetTypedefByIndex( asIScriptModule* module, asUINT index );

	// Dynamic binding between modules
	AS_API asUINT asModule_GetImportedFunctionCount( asIScriptModule* module );
	AS_API int asModule_GetImportedFunctionIndexByDecl( asIScriptModule* module, const char* decl );
	AS_API const char* asModule_GetImportedFunctionDeclaration( asIScriptModule* module, asUINT importIndex );
	AS_API const char* asModule_GetImportedFunctionSourceModule( asIScriptModule* module, asUINT importIndex );
	AS_API int asModule_BindImportedFunction( asIScriptModule* module, asUINT importIndex, asIScriptFunction* func );
	AS_API int asModule_UnbindImportedFunction( asIScriptModule* module, asUINT importIndex );
	AS_API int asModule_BindAllImportedFunctions( asIScriptModule* module );
	AS_API int asModule_UnbindAllImportedFunctions( asIScriptModule* module );

	// Byte code saving and loading
	AS_API int asModule_SaveByteCode( asIScriptModule* module, asBinaryStream* out, asBOOL_t stripDebugInfo );
	AS_API int asModule_LoadByteCode( asIScriptModule* module, asBinaryStream* in, asBOOL_t* wasDebugInfoStripped );

	// User data
	AS_API void* asModule_SetUserData( asIScriptModule* module, void* data, asPWORD type );
	AS_API void* asModule_GetUserData( asIScriptModule* module, asPWORD type );
	// endregion Interface declarations - module

	// region Interface declarations - context
	// Memory management
	AS_API int asContext_AddRef( asIScriptContext* context );
	AS_API int asContext_Release( asIScriptContext* context );

	// Miscellaneous
	AS_API asIScriptEngine* asContext_GetEngine( asIScriptContext* context );

	// Execution
	AS_API int asContext_Prepare( asIScriptContext* context, asIScriptFunction* func );
	AS_API int asContext_Unprepare( asIScriptContext* context );
	AS_API int asContext_Execute( asIScriptContext* context );
	AS_API int asContext_Abort( asIScriptContext* context );
	AS_API int asContext_Suspend( asIScriptContext* context );
	AS_API asEContextState asContext_GetState( asIScriptContext* context );
	AS_API int asContext_PushState( asIScriptContext* context );
	AS_API int asContext_PopState( asIScriptContext* context );
	AS_API asBOOL_t asContext_IsNested( asIScriptContext* context, asUINT* nestCount );

	// Object pointer for calling class methods
	AS_API int asContext_SetObject( asIScriptContext* context, void* obj );

	// Arguments
	AS_API int asContext_SetArgByte( asIScriptContext* context, asUINT arg, asBYTE value );
	AS_API int asContext_SetArgWord( asIScriptContext* context, asUINT arg, asWORD value );
	AS_API int asContext_SetArgDWord( asIScriptContext* context, asUINT arg, asDWORD value );
	AS_API int asContext_SetArgQWord( asIScriptContext* context, asUINT arg, asQWORD value );
	AS_API int asContext_SetArgFloat( asIScriptContext* context, asUINT arg, float value );
	AS_API int asContext_SetArgDouble( asIScriptContext* context, asUINT arg, double value );
	AS_API int asContext_SetArgAddress( asIScriptContext* context, asUINT arg, void* addr );
	AS_API int asContext_SetArgObject( asIScriptContext* context, asUINT arg, void* obj );
	AS_API int asContext_SetArgVarType( asIScriptContext* context, asUINT arg, void* ptr, int typeId );
	AS_API void* asContext_GetAddressOfArg( asIScriptContext* context, asUINT arg );

	// Return value
	AS_API asBYTE asContext_GetReturnByte( asIScriptContext* context );
	AS_API asWORD asContext_GetReturnWord( asIScriptContext* context );
	AS_API asDWORD asContext_GetReturnDWord( asIScriptContext* context );
	AS_API asQWORD asContext_GetReturnQWord( asIScriptContext* context );
	AS_API float asContext_GetReturnFloat( asIScriptContext* context );
	AS_API double asContext_GetReturnDouble( asIScriptContext* context );
	AS_API void* asContext_GetReturnAddress( asIScriptContext* context );
	AS_API void* asContext_GetReturnObject( asIScriptContext* context );
	AS_API void* asContext_GetAddressOfReturnValue( asIScriptContext* context );

	// Exception handling
	AS_API int asContext_SetException( asIScriptContext* context, const char* info, asBOOL_t allowCatch );
	AS_API int asContext_GetExceptionLineNumber( asIScriptContext* context, int* column, const char** sectionName );
	AS_API asIScriptFunction* asContext_GetExceptionFunction( asIScriptContext* context );
	AS_API const char* asContext_GetExceptionString( asIScriptContext* context );
	AS_API asBOOL_t asContext_WillExceptionBeCaught( asIScriptContext* context );
	AS_API int asContext_SetExceptionCallback( asIScriptContext* context, asFUNCTION_t callback, void* obj, int callConv );
	AS_API void asContext_ClearExceptionCallback( asIScriptContext* context );

	// Debugging
	AS_API int asContext_SetLineCallback( asIScriptContext* context, asFUNCTION_t callback, void* obj, int callConv );
	AS_API void asContext_ClearLineCallback( asIScriptContext* context );
	AS_API asUINT asContext_GetCallstackSize( asIScriptContext* context );
	AS_API asIScriptFunction* asContext_GetFunction( asIScriptContext* context, asUINT stackLevel );
	AS_API int asContext_GetLineNumber( asIScriptContext* context, asUINT stackLevel, int* column, const char** sectionName );
	AS_API int asContext_GetVarCount( asIScriptContext* context, asUINT stackLevel );
	AS_API int asContext_GetVar( asIScriptContext* context, asUINT varIndex, asUINT stackLevel, const char** name, int* typeId, asETypeModifiers* typeModifiers, asBOOL_t* isVarOnHeap, int* stackOffset );
	AS_API const char* asContext_GetVarDeclaration( asIScriptContext* context, asUINT varIndex, asUINT stackLevel, asBOOL_t includeNamespace );
	AS_API void* asContext_GetAddressOfVar( asIScriptContext* context, asUINT varIndex, asUINT stackLevel, asBOOL_t dontDereference, asBOOL_t returnAddressOfUnitializedObjects );
	AS_API asBOOL_t asContext_IsVarInScope( asIScriptContext* context, asUINT varIndex, asUINT stackLevel );
	AS_API int asContext_GetThisTypeId( asIScriptContext* context, asUINT stackLevel );
	AS_API void* asContext_GetThisPointer( asIScriptContext* context, asUINT stackLevel );
	AS_API asIScriptFunction* asContext_GetSystemFunction( asIScriptContext* context );

	// User data
	AS_API void* asContext_SetUserData( asIScriptContext* context, void* data, asPWORD type );
	AS_API void* asContext_GetUserData( asIScriptContext* context, asPWORD type );

	// Serialization
	AS_API int asContext_StartDeserialization( asIScriptContext* context );
	AS_API int asContext_FinishDeserialization( asIScriptContext* context );
	AS_API int asContext_PushFunction( asIScriptContext* context, asIScriptFunction* func, void* object );
	AS_API int asContext_GetStateRegisters( asIScriptContext* context, asUINT stackLevel, asIScriptFunction** callingSystemFunction, asIScriptFunction** initialFunction, asDWORD* origStackPointer, asDWORD* argumentsSize, asQWORD* valueRegister, void** objectRegister, asITypeInfo** objectTypeRegister );
	AS_API int asContext_GetCallStateRegisters( asIScriptContext* context, asUINT stackLevel, asDWORD* stackFramePointer, asIScriptFunction** currentFunction, asDWORD* programPointer, asDWORD* stackPointer, asDWORD* stackIndex );
	AS_API int asContext_SetStateRegisters( asIScriptContext* context, asUINT stackLevel, asIScriptFunction* callingSystemFunction, asIScriptFunction* initialFunction, asDWORD origStackPointer, asDWORD argumentsSize, asQWORD valueRegister, void* objectRegister, asITypeInfo* objectTypeRegister );
	AS_API int asContext_SetCallStateRegisters( asIScriptContext* context, asUINT stackLevel, asDWORD stackFramePointer, asIScriptFunction* currentFunction, asDWORD programPointer, asDWORD stackPointer, asDWORD stackIndex );
	AS_API int asContext_GetArgsOnStackCount( asIScriptContext* context, asUINT stackLevel );
	AS_API int asContext_GetArgOnStack( asIScriptContext* context, asUINT stackLevel, asUINT arg, int* typeId, asUINT* flags, void** address );
	// endregion Interface declarations - context

	// region Interface declarations - generic
	// Miscellaneous
	AS_API asIScriptEngine* asGeneric_GetEngine( asIScriptGeneric* generic );
	AS_API asIScriptFunction* asGeneric_GetFunction( asIScriptGeneric* generic );
	AS_API void* asGeneric_GetAuxiliary( asIScriptGeneric* generic );

	// Object
	AS_API void* asGeneric_GetObject( asIScriptGeneric* generic );
	AS_API int asGeneric_GetObjectTypeId( asIScriptGeneric* generic );

	// Arguments
	AS_API int asGeneric_GetArgCount( asIScriptGeneric* generic );
	AS_API int asGeneric_GetArgTypeId( asIScriptGeneric* generic, asUINT arg, asDWORD* flags );
	AS_API asBYTE asGeneric_GetArgByte( asIScriptGeneric* generic, asUINT arg );
	AS_API asWORD asGeneric_GetArgWord( asIScriptGeneric* generic, asUINT arg );
	AS_API asDWORD asGeneric_GetArgDWord( asIScriptGeneric* generic, asUINT arg );
	AS_API asQWORD asGeneric_GetArgQWord( asIScriptGeneric* generic, asUINT arg );
	AS_API float asGeneric_GetArgFloat( asIScriptGeneric* generic, asUINT arg );
	AS_API double asGeneric_GetArgDouble( asIScriptGeneric* generic, asUINT arg );
	AS_API void* asGeneric_GetArgAddress( asIScriptGeneric* generic, asUINT arg );
	AS_API void* asGeneric_GetArgObject( asIScriptGeneric* generic, asUINT arg );
	AS_API void* asGeneric_GetAddressOfArg( asIScriptGeneric* generic, asUINT arg );

	// Return value
	AS_API int asGeneric_GetReturnTypeId( asIScriptGeneric* generic, asDWORD* flags );
	AS_API int asGeneric_SetReturnByte( asIScriptGeneric* generic, asBYTE val );
	AS_API int asGeneric_SetReturnWord( asIScriptGeneric* generic, asWORD val );
	AS_API int asGeneric_SetReturnDWord( asIScriptGeneric* generic, asDWORD val );
	AS_API int asGeneric_SetReturnQWord( asIScriptGeneric* generic, asQWORD val );
	AS_API int asGeneric_SetReturnFloat( asIScriptGeneric* generic, float val );
	AS_API int asGeneric_SetReturnDouble( asIScriptGeneric* generic, double val );
	AS_API int asGeneric_SetReturnAddress( asIScriptGeneric* generic, void* addr );
	AS_API int asGeneric_SetReturnObject( asIScriptGeneric* generic, void* obj );
	AS_API void* asGeneric_GetAddressOfReturnLocation( asIScriptGeneric* generic );
	// endregion Interface declarations - generic

	// region Interface declarations - object
	// Memory management
	AS_API int asObject_AddRef( asIScriptObject* object );
	AS_API int asObject_Release( asIScriptObject* object );
	AS_API asILockableSharedBool* asObject_GetWeakRefFlag( asIScriptObject* object );

	// Type info
	AS_API int asObject_GetTypeId( asIScriptObject* object );
	AS_API asITypeInfo* asObject_GetObjectType( asIScriptObject* object );

	// Class properties
	AS_API asUINT asObject_GetPropertyCount( asIScriptObject* object );
	AS_API int asObject_GetPropertyTypeId( asIScriptObject* object, asUINT prop );
	AS_API const char* asObject_GetPropertyName( asIScriptObject* object, asUINT prop );
	AS_API void* asObject_GetAddressOfProperty( asIScriptObject* object, asUINT prop );

	// Miscellaneous
	AS_API asIScriptEngine* asObject_GetEngine( asIScriptObject* object );
	AS_API int asObject_CopyFrom( asIScriptObject* object, const asIScriptObject* other );

	// User data
	AS_API void* asObject_SetUserData( asIScriptObject* object, void* data, asPWORD type );
	AS_API void* asObject_GetUserData( asIScriptObject* object, asPWORD type );
	// endregion Interface declarations - object

	// region Interface declarations - type info
	// Miscellaneous
	AS_API asIScriptEngine* asTypeInfo_GetEngine( asITypeInfo* info );
	AS_API const char* asTypeInfo_GetConfigGroup( asITypeInfo* info );
	AS_API asDWORD asTypeInfo_GetAccessMask( asITypeInfo* info );
	AS_API asIScriptModule* asTypeInfo_GetModule( asITypeInfo* info );

	// Memory management
	AS_API int asTypeInfo_AddRef( asITypeInfo* info );
	AS_API int asTypeInfo_Release( asITypeInfo* info );

	// Type info
	AS_API const char* asTypeInfo_GetName( asITypeInfo* info );
	AS_API const char* asTypeInfo_GetNamespace( asITypeInfo* info );
	AS_API asITypeInfo* asTypeInfo_GetBaseType( asITypeInfo* info );
	AS_API asBOOL_t asTypeInfo_DerivesFrom( asITypeInfo* info, const asITypeInfo* objType );
	AS_API asDWORD asTypeInfo_GetFlags( asITypeInfo* info );
	AS_API asUINT asTypeInfo_GetSize( asITypeInfo* info );
	AS_API int asTypeInfo_GetTypeId( asITypeInfo* info );
	AS_API int asTypeInfo_GetSubTypeId( asITypeInfo* info, asUINT subTypeIndex );
	AS_API asITypeInfo* asTypeInfo_GetSubType( asITypeInfo* info, asUINT subTypeIndex );
	AS_API asUINT asTypeInfo_GetSubTypeCount( asITypeInfo* info );

	// Interfaces
	AS_API asUINT asTypeInfo_GetInterfaceCount( asITypeInfo* info );
	AS_API asITypeInfo* asTypeInfo_GetInterface( asITypeInfo* info, asUINT index );
	AS_API asBOOL_t asTypeInfo_Implements( asITypeInfo* info, const asITypeInfo* objType );

	// Factories
	AS_API asUINT asTypeInfo_GetFactoryCount( asITypeInfo* info );
	AS_API asIScriptFunction* asTypeInfo_GetFactoryByIndex( asITypeInfo* info, asUINT index );
	AS_API asIScriptFunction* asTypeInfo_GetFactoryByDecl( asITypeInfo* info, const char* decl );

	// Methods
	AS_API asUINT asTypeInfo_GetMethodCount( asITypeInfo* info );
	AS_API asIScriptFunction* asTypeInfo_GetMethodByIndex( asITypeInfo* info, asUINT index, asBOOL_t getVirtual );
	AS_API asIScriptFunction* asTypeInfo_GetMethodByName( asITypeInfo* info, const char* name, asBOOL_t getVirtual );
	AS_API asIScriptFunction* asTypeInfo_GetMethodByDecl( asITypeInfo* info, const char* decl, asBOOL_t getVirtual );

	// Properties
	AS_API asUINT asTypeInfo_GetPropertyCount( asITypeInfo* info );
	AS_API int asTypeInfo_GetProperty( asITypeInfo* info, asUINT index, const char** name, int* typeId, asBOOL_t* isPrivate, asBOOL_t* isProtected, int* offset, asBOOL_t* isReference, asDWORD* accessMask, int* compositeOffset, asBOOL_t* isCompositeIndirect );
	AS_API const char* asTypeInfo_GetPropertyDeclaration( asITypeInfo* info, asUINT index, asBOOL_t includeNamespace );

	// Behaviours
	AS_API asUINT asTypeInfo_GetBehaviourCount( asITypeInfo* info );
	AS_API asIScriptFunction* asTypeInfo_GetBehaviourByIndex( asITypeInfo* info, asUINT index, asEBehaviours* outBehaviour );

	// Child types
	AS_API asUINT asTypeInfo_GetChildFuncdefCount( asITypeInfo* info );
	AS_API asITypeInfo* asTypeInfo_GetChildFuncdef( asITypeInfo* info, asUINT index );
	AS_API asITypeInfo* asTypeInfo_GetParentType( asITypeInfo* info );

	// Enums
	AS_API asUINT asTypeInfo_GetEnumValueCount( asITypeInfo* info );
	AS_API const char* asTypeInfo_GetEnumValueByIndex( asITypeInfo* info, asUINT index, int* outValue );

	// Typedef
	AS_API int asTypeInfo_GetTypedefTypeId( asITypeInfo* info );

	// Funcdef
	AS_API asIScriptFunction* asTypeInfo_GetFuncdefSignature( asITypeInfo* info );

	// User data
	AS_API void* asTypeInfo_SetUserData( asITypeInfo* info, void* data, asPWORD type );
	AS_API void* asTypeInfo_GetUserData( asITypeInfo* info, asPWORD type );
	// endregion Interface declarations - type info

	// region Interface declarations - function
	AS_API asIScriptEngine* asFunction_GetEngine( asIScriptFunction* function );

	// Memory management
	AS_API int asFunction_AddRef( asIScriptFunction* function );
	AS_API int asFunction_Release( asIScriptFunction* function );

	// Miscellaneous
	AS_API int asFunction_GetId( asIScriptFunction* function );
	AS_API asEFuncType asFunction_GetFuncType( asIScriptFunction* function );
	AS_API const char* asFunction_GetModuleName( asIScriptFunction* function );
	AS_API asIScriptModule* asFunction_GetModule( asIScriptFunction* function );
	AS_API const char* asFunction_GetScriptSectionName( asIScriptFunction* function );
	AS_API const char* asFunction_GetConfigGroup( asIScriptFunction* function );
	AS_API asDWORD asFunction_GetAccessMask( asIScriptFunction* function );
	AS_API void* asFunction_GetAuxiliary( asIScriptFunction* function );

	// Function signature
	AS_API asITypeInfo* asFunction_GetObjectType( asIScriptFunction* function );
	AS_API const char* asFunction_GetObjectName( asIScriptFunction* function );
	AS_API const char* asFunction_GetName( asIScriptFunction* function );
	AS_API const char* asFunction_GetNamespace( asIScriptFunction* function );
	AS_API const char* asFunction_GetDeclaration( asIScriptFunction* function, asBOOL_t includeObjectName, asBOOL_t includeNamespace, asBOOL_t includeParamNames );
	AS_API asBOOL_t asFunction_IsReadOnly( asIScriptFunction* function );
	AS_API asBOOL_t asFunction_IsPrivate( asIScriptFunction* function );
	AS_API asBOOL_t asFunction_IsProtected( asIScriptFunction* function );
	AS_API asBOOL_t asFunction_IsFinal( asIScriptFunction* function );
	AS_API asBOOL_t asFunction_IsOverride( asIScriptFunction* function );
	AS_API asBOOL_t asFunction_IsShared( asIScriptFunction* function );
	AS_API asBOOL_t asFunction_IsExplicit( asIScriptFunction* function );
	AS_API asBOOL_t asFunction_IsProperty( asIScriptFunction* function );
	AS_API asUINT asFunction_GetParamCount( asIScriptFunction* function );
	AS_API int asFunction_GetParam( asIScriptFunction* function, asUINT index, int* typeId, asDWORD* flags, const char** name, const char** defaultArg );
	AS_API int asFunction_GetReturnTypeId( asIScriptFunction* function, asDWORD* flags );

	// Type id for function pointers
	AS_API int asFunction_GetTypeId( asIScriptFunction* function );
	AS_API asBOOL_t asFunction_IsCompatibleWithTypeId( asIScriptFunction* function, int typeId );

	// Delegates
	AS_API void* asFunction_GetDelegateObject( asIScriptFunction* function );
	AS_API asITypeInfo* asFunction_GetDelegateObjectType( asIScriptFunction* function );
	AS_API asIScriptFunction* asFunction_GetDelegateFunction( asIScriptFunction* function );

	// Debug information
	AS_API asUINT asFunction_GetVarCount( asIScriptFunction* function );
	AS_API int asFunction_GetVar( asIScriptFunction* function, asUINT index, const char** name, int* typeId );
	AS_API const char* asFunction_GetVarDecl( asIScriptFunction* function, asUINT index, asBOOL_t includeNamespace );
	AS_API int asFunction_FindNextLineWithCode( asIScriptFunction* function, int line );

	// For JIT compilation
	AS_API asDWORD* asFunction_GetByteCode( asIScriptFunction* function, asUINT* length );

	// User data
	AS_API void* asFunction_SetUserData( asIScriptFunction* function, void* userData, asPWORD type );
	AS_API void* asFunction_GetUserData( asIScriptFunction* function, asPWORD type );
	// endregion Interface declarations - function

	// region Interface declarations - lockable shared asBOOL_t
	// Memory management
	AS_API int asLockableSharedBool_AddRef( asILockableSharedBool* lockable );
	AS_API int asLockableSharedBool_Release( asILockableSharedBool* lockable );

	// Value
	AS_API asBOOL_t asLockableSharedBool_Get( asILockableSharedBool* lockable );
	AS_API void asLockableSharedBool_Set( asILockableSharedBool* lockable, asBOOL_t val );

	// Thread management
	AS_API void asLockableSharedBool_Lock( asILockableSharedBool* lockable );
	AS_API void asLockableSharedBool_Unlock( asILockableSharedBool* lockable );
	// endregion Interface declarations - lockable shared asBOOL_t

	#ifdef __cplusplus
		}
	#endif
#endif
