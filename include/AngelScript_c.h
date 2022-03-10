//
// Created by ENDERZOMBI102 on 09/03/2022.
//

#ifndef ANGELSCRIPT_C_H
#define ANGELSCRIPT_C_H

#ifdef __cplusplus
	#define BEGIN_AS_NAMESPACE extern "C" {
	#define END_AS_NAMESPACE }
#else
	#define BEGIN_AS_NAMESPACE
	#define END_AS_NAMESPACE
#endif

BEGIN_AS_NAMESPACE

// AngelScript version

#define ANGELSCRIPT_VERSION        23501
#define ANGELSCRIPT_VERSION_STRING "2.35.1"

// Data types
typedef struct as_IScriptEngine as_IScriptEngine_t;
typedef struct as_IScriptModule as_IScriptModule_t;
typedef struct as_IScriptContext as_IScriptContext_t;
typedef struct as_IScriptGeneric as_IScriptGeneric_t;
typedef struct as_IScriptObject as_IScriptObject_t;
typedef struct as_ITypeInfo as_ITypeInfo_t;
typedef struct as_IScriptFunction as_IScriptFunction_t;
typedef struct as_IBinaryStream as_IBinaryStream_t;
typedef struct as_IJITCompiler as_IJITCompiler_t;
typedef struct as_IThreadManager as_IThreadManager_t;
typedef struct as_ILockableSharedBool as_ILockableSharedBool_t;
typedef struct as_IStringFactory as_IStringFactory_t;

// Enumerations and constants

// Return codes
typedef enum as_ERetCodes {
	AS_SUCCESS = 0,
	AS_ERROR = -1,
	AS_CONTEXT_ACTIVE = -2,
	AS_CONTEXT_NOT_FINISHED = -3,
	AS_CONTEXT_NOT_PREPARED = -4,
	AS_INVALID_ARG = -5,
	AS_NO_FUNCTION = -6,
	AS_NOT_SUPPORTED = -7,
	AS_INVALID_NAME = -8,
	AS_NAME_TAKEN = -9,
	AS_INVALID_DECLARATION = -10,
	AS_INVALID_OBJECT = -11,
	AS_INVALID_TYPE = -12,
	AS_ALREADY_REGISTERED = -13,
	AS_MULTIPLE_FUNCTIONS = -14,
	AS_NO_MODULE = -15,
	AS_NO_GLOBAL_VAR = -16,
	AS_INVALID_CONFIGURATION = -17,
	AS_INVALID_INTERFACE = -18,
	AS_CANT_BIND_ALL_FUNCTIONS = -19,
	AS_LOWER_ARRAY_DIMENSION_NOT_REGISTERED = -20,
	AS_WRONG_CONFIG_GROUP = -21,
	AS_CONFIG_GROUP_IS_IN_USE = -22,
	AS_ILLEGAL_BEHAVIOUR_FOR_TYPE = -23,
	AS_WRONG_CALLING_CONV = -24,
	AS_BUILD_IN_PROGRESS = -25,
	AS_INIT_GLOBAL_VARS_FAILED = -26,
	AS_OUT_OF_MEMORY = -27,
	AS_MODULE_IS_IN_USE = -28
} as_ERetCodes_t;

// Engine properties
typedef enum as_EEngineProp {
	AS_EP_ALLOW_UNSAFE_REFERENCES = 1,
	AS_EP_OPTIMIZE_BYTECODE = 2,
	AS_EP_COPY_SCRIPT_SECTIONS = 3,
	AS_EP_MAX_STACK_SIZE = 4,
	AS_EP_USE_CHARACTER_LITERALS = 5,
	AS_EP_ALLOW_MULTILINE_STRINGS = 6,
	AS_EP_ALLOW_IMPLICIT_HANDLE_TYPES = 7,
	AS_EP_BUILD_WITHOUT_LINE_CUES = 8,
	AS_EP_INIT_GLOBAL_VARS_AFTER_BUILD = 9,
	AS_EP_REQUIRE_ENUM_SCOPE = 10,
	AS_EP_SCRIPT_SCANNER = 11,
	AS_EP_INCLUDE_JIT_INSTRUCTIONS = 12,
	AS_EP_STRING_ENCODING = 13,
	AS_EP_PROPERTY_ACCESSOR_MODE = 14,
	AS_EP_EXPAND_DEF_ARRAY_TO_TMPL = 15,
	AS_EP_AUTO_GARBAGE_COLLECT = 16,
	AS_EP_DISALLOW_GLOBAL_VARS = 17,
	AS_EP_ALWAYS_IMPL_DEFAULT_CONSTRUCT = 18,
	AS_EP_COMPILER_WARNINGS = 19,
	AS_EP_DISALLOW_VALUE_ASSIGN_FOR_REF_TYPE = 20,
	AS_EP_ALTER_SYNTAX_NAMED_ARGS = 21,
	AS_EP_DISABLE_INTEGER_DIVISION = 22,
	AS_EP_DISALLOW_EMPTY_LIST_ELEMENTS = 23,
	AS_EP_PRIVATE_PROP_AS_PROTECTED = 24,
	AS_EP_ALLOW_UNICODE_IDENTIFIERS = 25,
	AS_EP_HEREDOC_TRIM_MODE = 26,
	AS_EP_MAX_NESTED_CALLS = 27,
	AS_EP_GENERIC_CALL_MODE = 28,
	AS_EP_INIT_STACK_SIZE = 29,
	AS_EP_INIT_CALL_STACK_SIZE = 30,
	AS_EP_MAX_CALL_STACK_SIZE = 31,

	AS_EP_LAST_PROPERTY
} as_EEngineProp_t;

// Calling conventions
typedef enum as_ECallConvTypes {
	AS_CALL_CDECL = 0,
	AS_CALL_STDCALL = 1,
	AS_CALL_THISCALL_ASGLOBAL = 2,
	AS_CALL_THISCALL = 3,
	AS_CALL_CDECL_OBJLAST = 4,
	AS_CALL_CDECL_OBJFIRST = 5,
	AS_CALL_GENERIC = 6,
	AS_CALL_THISCALL_OBJLAST = 7,
	AS_CALL_THISCALL_OBJFIRST = 8
} as_ECallConvTypes_t;

// Object type flags
typedef enum as_EObjTypeFlags {
	AS_OBJ_REF = (1 << 0),
	AS_OBJ_VALUE = (1 << 1),
	AS_OBJ_GC = (1 << 2),
	AS_OBJ_POD = (1 << 3),
	AS_OBJ_NOHANDLE = (1 << 4),
	AS_OBJ_SCOPED = (1 << 5),
	AS_OBJ_TEMPLATE = (1 << 6),
	AS_OBJ_ASHANDLE = (1 << 7),
	AS_OBJ_APP_CLASS = (1 << 8),
	AS_OBJ_APP_CLASS_CONSTRUCTOR = (1 << 9),
	AS_OBJ_APP_CLASS_DESTRUCTOR = (1 << 10),
	AS_OBJ_APP_CLASS_ASSIGNMENT = (1 << 11),
	AS_OBJ_APP_CLASS_COPY_CONSTRUCTOR = (1 << 12),
	AS_OBJ_APP_CLASS_C = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_CONSTRUCTOR),
	AS_OBJ_APP_CLASS_CD = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_CONSTRUCTOR + AS_OBJ_APP_CLASS_DESTRUCTOR),
	AS_OBJ_APP_CLASS_CA = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_CONSTRUCTOR + AS_OBJ_APP_CLASS_ASSIGNMENT),
	AS_OBJ_APP_CLASS_CK = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_CONSTRUCTOR + AS_OBJ_APP_CLASS_COPY_CONSTRUCTOR),
	AS_OBJ_APP_CLASS_CDA = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_CONSTRUCTOR + AS_OBJ_APP_CLASS_DESTRUCTOR +
	                        AS_OBJ_APP_CLASS_ASSIGNMENT),
	AS_OBJ_APP_CLASS_CDK = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_CONSTRUCTOR + AS_OBJ_APP_CLASS_DESTRUCTOR +
	                        AS_OBJ_APP_CLASS_COPY_CONSTRUCTOR),
	AS_OBJ_APP_CLASS_CAK = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_CONSTRUCTOR + AS_OBJ_APP_CLASS_ASSIGNMENT +
	                        AS_OBJ_APP_CLASS_COPY_CONSTRUCTOR),
	AS_OBJ_APP_CLASS_CDAK = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_CONSTRUCTOR + AS_OBJ_APP_CLASS_DESTRUCTOR +
	                         AS_OBJ_APP_CLASS_ASSIGNMENT + AS_OBJ_APP_CLASS_COPY_CONSTRUCTOR),
	AS_OBJ_APP_CLASS_D = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_DESTRUCTOR),
	AS_OBJ_APP_CLASS_DA = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_DESTRUCTOR + AS_OBJ_APP_CLASS_ASSIGNMENT),
	AS_OBJ_APP_CLASS_DK = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_DESTRUCTOR + AS_OBJ_APP_CLASS_COPY_CONSTRUCTOR),
	AS_OBJ_APP_CLASS_DAK = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_DESTRUCTOR + AS_OBJ_APP_CLASS_ASSIGNMENT +
	                        AS_OBJ_APP_CLASS_COPY_CONSTRUCTOR),
	AS_OBJ_APP_CLASS_A = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_ASSIGNMENT),
	AS_OBJ_APP_CLASS_AK = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_ASSIGNMENT + AS_OBJ_APP_CLASS_COPY_CONSTRUCTOR),
	AS_OBJ_APP_CLASS_K = (AS_OBJ_APP_CLASS + AS_OBJ_APP_CLASS_COPY_CONSTRUCTOR),
	AS_OBJ_APP_CLASS_MORE_CONSTRUCTORS = (1 << 31),
	AS_OBJ_APP_PRIMITIVE = (1 << 13),
	AS_OBJ_APP_FLOAT = (1 << 14),
	AS_OBJ_APP_ARRAY = (1 << 15),
	AS_OBJ_APP_CLASS_ALLINTS = (1 << 16),
	AS_OBJ_APP_CLASS_ALLFLOATS = (1 << 17),
	AS_OBJ_NOCOUNT = (1 << 18),
	AS_OBJ_APP_CLASS_ALIGN8 = (1 << 19),
	AS_OBJ_IMPLICIT_HANDLE = (1 << 20),
	AS_OBJ_MASK_VALID_FLAGS = 0x801FFFFF,
	// Internal flags
	AS_OBJ_SCRIPT_OBJECT = (1 << 21),
	AS_OBJ_SHARED = (1 << 22),
	AS_OBJ_NOINHERIT = (1 << 23),
	AS_OBJ_FUNCDEF = (1 << 24),
	AS_OBJ_LIST_PATTERN = (1 << 25),
	AS_OBJ_ENUM = (1 << 26),
	AS_OBJ_TEMPLATE_SUBTYPE = (1 << 27),
	AS_OBJ_TYPEDEF = (1 << 28),
	AS_OBJ_ABSTRACT = (1 << 29),
	AS_OBJ_APP_ALIGN16 = (1 << 30)
} as_EObjTypeFlags_t;

// Behaviours
typedef enum as_EBehaviours {
	// Value object memory management
	AS_BEHAVE_CONSTRUCT,
	AS_BEHAVE_LIST_CONSTRUCT,
	AS_BEHAVE_DESTRUCT,

	// Reference object memory management
	AS_BEHAVE_FACTORY,
	AS_BEHAVE_LIST_FACTORY,
	AS_BEHAVE_ADDREF,
	AS_BEHAVE_RELEASE,
	AS_BEHAVE_GET_WEAKREF_FLAG,

	// Object operators
	AS_BEHAVE_TEMPLATE_CALLBACK,

	// Garbage collection behaviours
	AS_BEHAVE_FIRST_GC,
	AS_BEHAVE_GETREFCOUNT = AS_BEHAVE_FIRST_GC,
	AS_BEHAVE_SETGCFLAG,
	AS_BEHAVE_GETGCFLAG,
	AS_BEHAVE_ENUMREFS,
	AS_BEHAVE_RELEASEREFS,
	AS_BEHAVE_LAST_GC = AS_BEHAVE_RELEASEREFS,

	AS_BEHAVE_MAX
} as_EBehaviours_t;

// Context states
typedef enum as_EContextState {
	AS_EXECUTION_FINISHED = 0,
	AS_EXECUTION_SUSPENDED = 1,
	AS_EXECUTION_ABORTED = 2,
	AS_EXECUTION_EXCEPTION = 3,
	AS_EXECUTION_PREPARED = 4,
	AS_EXECUTION_UNINITIALIZED = 5,
	AS_EXECUTION_ACTIVE = 6,
	AS_EXECUTION_ERROR = 7
} as_EContextState_t;

// Message types
typedef enum as_EMsgType {
	AS_MSGTYPE_ERROR = 0,
	AS_MSGTYPE_WARNING = 1,
	AS_MSGTYPE_INFORMATION = 2
} as_EMsgType_t;

// Garbage collector flags
typedef enum as_EGCFlags {
	AS_GC_FULL_CYCLE = 1,
	AS_GC_ONE_STEP = 2,
	AS_GC_DESTROY_GARBAGE = 4,
	AS_GC_DETECT_GARBAGE = 8
} as_EGCFlags_t;

// Token clas_ses
typedef enum as_ETokenClass {
	AS_TC_UNKNOWN = 0,
	AS_TC_KEYWORD = 1,
	AS_TC_VALUE = 2,
	AS_TC_IDENTIFIER = 3,
	AS_TC_COMMENT = 4,
	AS_TC_WHITESPACE = 5
} as_ETokenClass_t;

// Type id flags
typedef enum as_ETypeIdFlags {
	AS_TYPEID_VOID = 0,
	AS_TYPEID_BOOL = 1,
	AS_TYPEID_INT8 = 2,
	AS_TYPEID_INT16 = 3,
	AS_TYPEID_INT32 = 4,
	AS_TYPEID_INT64 = 5,
	AS_TYPEID_UINT8 = 6,
	AS_TYPEID_UINT16 = 7,
	AS_TYPEID_UINT32 = 8,
	AS_TYPEID_UINT64 = 9,
	AS_TYPEID_FLOAT = 10,
	AS_TYPEID_DOUBLE = 11,
	AS_TYPEID_OBJHANDLE = 0x40000000,
	AS_TYPEID_HANDLETOCONST = 0x20000000,
	AS_TYPEID_MASK_OBJECT = 0x1C000000,
	AS_TYPEID_APPOBJECT = 0x04000000,
	AS_TYPEID_SCRIPTOBJECT = 0x08000000,
	AS_TYPEID_TEMPLATE = 0x10000000,
	AS_TYPEID_MASK_SEQNBR = 0x03FFFFFF
} as_ETypeIdFlags_t;

// Type modifiers
typedef enum as_ETypeModifiers {
	AS_TM_NONE = 0,
	AS_TM_INREF = 1,
	AS_TM_OUTREF = 2,
	AS_TM_INOUTREF = 3,
	AS_TM_CONST = 4
} as_ETypeModifiers_t;

// GetModule flags
typedef enum as_EGMFlags {
	AS_GM_ONLY_IF_EXISTS = 0,
	AS_GM_CREATE_IF_NOT_EXISTS = 1,
	AS_GM_ALWAYS_CREATE = 2
} as_EGMFlags_t;

// Compile flags
typedef enum as_ECompileFlags {
	AS_COMP_ADD_TO_MODULE = 1
} as_ECompileFlags_t;

// Function types
typedef enum as_EFuncType {
	AS_FUNC_DUMMY = -1,
	AS_FUNC_SYSTEM = 0,
	AS_FUNC_SCRIPT = 1,
	AS_FUNC_INTERFACE = 2,
	AS_FUNC_VIRTUAL = 3,
	AS_FUNC_FUNCDEF = 4,
	AS_FUNC_IMPORTED = 5,
	AS_FUNC_DELEGATE = 6
} as_EFuncType_t;

//
// asBYTE  =  8 bits
// asWORD  = 16 bits
// asDWORD = 32 bits
// asQWORD = 64 bits
// asPWORD = size of pointer
//
typedef signed char asINT8;
typedef signed short asINT16;
typedef unsigned char asBYTE;
typedef unsigned short asWORD;
typedef unsigned int asUINT;

#if (defined(_MSC_VER) && _MSC_VER <= 1200) || defined(__S3E__) || (defined(_MSC_VER) && defined(__clang__))
	// size_t is not really correct, since it only guaranteed to be large enough to hold the segment size.
	// For example, on 16bit systems the size_t may be 16bits only even if pointers are 32bit. But nobody
	// is likely to use MSVC6 to compile for 16bit systems anymore, so this should be ok.
	typedef size_t         asPWORD;
#else
	typedef uintptr_t asPWORD;
#endif
#ifdef __LP64__
	typedef unsigned int  asDWORD;
	typedef unsigned long asQWORD;
	typedef long asINT64;
#else
	typedef unsigned long as_DWORD;
	#if !defined(_MSC_VER) && (defined(__GNUC__) || defined(__MWERKS__) || defined(__SUNPRO_CC) || defined(__psp2__))
		typedef uint64_t asQWORD;
		typedef int64_t asINT64;
	#else
		typedef unsigned __int64 asQWORD;
		typedef __int64 asINT64;
	#endif
#endif

// Is the target a 64bit system?
#if defined(__LP64__) || defined(__amd64__) || defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(_M_ARM64)
	#ifndef AS_64BIT_PTR
		#define AS_64BIT_PTR
	#endif
#endif

typedef void (*as_FUNCTION_t)();
typedef void (*as_GENFUNC_t)(as_IScriptGeneric_t *);
typedef void *(*as_ALLOCFUNC_t)(size_t);
typedef void (*as_FREEFUNC_t)(void *);
typedef void (*as_CLEANENGINEFUNC_t)(as_IScriptEngine_t *);
typedef void (*as_CLEANMODULEFUNC_t)(as_IScriptModule_t *);
typedef void (*as_CLEANCONTEXTFUNC_t)(as_IScriptContext_t *);
typedef void (*as_CLEANFUNCTIONFUNC_t)(as_IScriptFunction_t *);
typedef void (*as_CLEANTYPEINFOFUNC_t)(as_ITypeInfo_t *);
typedef void (*as_CLEANSCRIPTOBJECTFUNC_t)(as_IScriptObject_t *);
typedef as_IScriptContext_t *(*as_REQUESTCONTEXTFUNC_t)(as_IScriptEngine_t *, void *);
typedef void (*as_RETURNCONTEXTFUNC_t)(as_IScriptEngine_t *, as_IScriptContext_t *, void *);
typedef void (*as_CIRCULARREFFUNC_t)(as_ITypeInfo_t *, const void *, void *);

// Check if the compiler can use C++11 features
#if !defined(_MSC_VER) || _MSC_VER >= 1700   // MSVC 2012
	#if !defined(__GNUC__) || defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)  // gnuc 4.7 or clang
		#if !(defined(__GNUC__) && defined(__cplusplus) && __cplusplus < 201103L) // gnuc and clang require compiler flag -std=c++11
			#if !defined(__SUNPRO_CC) // Oracle Solaris Studio
				#define AS_CAN_USE_CPP11 1
			#endif
		#endif
	#endif
#endif

// This macro does basically the same thing as offsetof defined in stddef.h, but
// GNUC should not complain about the usage as I'm not using 0 as the base pointer.
#define asOFFSET(s, m) ( (int) (size_t) ( &reinterpret_cast<s*>(100000)->m ) - 100000 )

#define asFUNCTION(f) asFunctionPtr(f)
#define asFUNCTIONPR(f, p, r) asFunctionPtr((void (*)())((r (*)p)(f)))

#ifndef AS_NO_CLASS_METHODS

	typedef struct as_CUnknownClass as_CUnknownClass_t;
	typedef void (asCUnknownClass::*as_METHOD_t)();

	typedef struct as_SFuncPtr as_SFuncPtr_t;

	#define AS_METHOD_AMBIGUITY_CAST(t) (t)

	#define as_METHOD(c, m) asSMethodPtr<sizeof(void (c::*)())>::Convert((void (c::*)())(&c::m))
	#define as_METHODPR(c, m, p, r) asSMethodPtr<sizeof(void (c::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(r (c::*)p)(&c::m))

#else // Class methods are disabled

	struct as_SFuncPtr_t {
		as_SFuncPtr_t(asBYTE f) {
			for ( int n = 0; n < sizeof(ptr.dummy); n++ )
				ptr.dummy[n] = 0;
			flag = f;
		}

		union {
			char dummy[25]; // largest known class method pointer
			struct {asFUNCTION_t func; char dummy[25-sizeof(asFUNCTION_t)];} f;
		} ptr;
		asBYTE flag; // 1 = generic, 2 = global func
	};

#endif

typedef struct as_SMessageInfo {
	const char *section;
	int row;
	int col;
	as_EMsgType_t type;
	const char *message;
} as_SMessageInfo_t;


// API functions

// ANGELSCRIPT_EXPORT is defined when compiling the dll or lib
// ANGELSCRIPT_DLL_LIBRARY_IMPORT is defined when dynamically linking to the
// dll through the link lib automatically generated by MSVC++
// ANGELSCRIPT_DLL_MANUAL_IMPORT is defined when manually loading the dll
// Don't define anything when linking statically to the lib

#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__)
	#if defined(ANGELSCRIPT_EXPORT)
		#define AS_API __declspec(dllexport)
	#elif defined(ANGELSCRIPT_DLL_LIBRARY_IMPORT)
		#define AS_API __declspec(dllimport)
	#else // statically linked library
		#define AS_API
	#endif
#elif defined(__GNUC__)
	#if defined(ANGELSCRIPT_EXPORT)
		#define AS_API __attribute__((visibility ("default")))
	#else
		#define AS_API
	#endif
#else
	#define AS_API
#endif

#ifndef ANGELSCRIPT_DLL_MANUAL_IMPORT
	// Engine
	AS_API as_IScriptEngine_t *asCreateScriptEngine(as_DWORD version = ANGELSCRIPT_VERSION);
	AS_API const char *asGetLibraryVersion();
	AS_API const char *asGetLibraryOptions();

	// Context
	AS_API as_IScriptContext_t *asGetActiveContext();

	// Thread support
	AS_API int asPrepareMultithread(as_IThreadManager_t *externalMgr = 0);
	AS_API void asUnprepareMultithread();
	AS_API as_IThreadManager_t *asGetThreadManager();
	AS_API void asAcquireExclusiveLock();
	AS_API void asReleaseExclusiveLock();
	AS_API void asAcquireSharedLock();
	AS_API void asReleaseSharedLock();
	AS_API int asAtomicInc(int &value);
	AS_API int asAtomicDec(int &value);
	AS_API int asThreadCleanup();

	// Memory management
	AS_API int asSetGlobalMemoryFunctions(as_ALLOCFUNC_t allocFunc, as_FREEFUNC_t freeFunc);
	AS_API int asResetGlobalMemoryFunctions();
	AS_API void *asAllocMem(size_t size);
	AS_API void asFreeMem(void *mem);

	// Auxiliary
	AS_API as_ILockableSharedBool_t *asCreateLockableSharedBool();
#endif // ANGELSCRIPT_DLL_MANUAL_IMPORT

// Interface declarations

struct as_IScriptEngine {
public:
	// Memory management
	virtual int AddRef() const = 0;

	virtual int Release() const = 0;

	virtual int ShutDownAndRelease() = 0;

	// Engine properties
	virtual int SetEngineProperty(as_SMessageInfo_t property, asPWORD value) = 0;

	virtual asPWORD GetEngineProperty(as_SMessageInfo_t property) const = 0;

	// Compiler messages
	virtual int SetMessageCallback(const as_SFuncPtr_t &callback, void *obj, as_DWORD callConv) = 0;

	virtual int ClearMessageCallback() = 0;

	virtual int WriteMessage(const char *section, int row, int col, as_EMsgType_t type, const char *message) = 0;

	// JIT Compiler
	virtual int SetJITCompiler(as_IJITCompiler_t *compiler) = 0;

	virtual as_IJITCompiler_t *GetJITCompiler() const = 0;

	// Global functions
	virtual int RegisterGlobalFunction(const char *declaration, const as_SFuncPtr_t &funcPointer, as_DWORD callConv,
	                                   void *auxiliary = 0) = 0;

	virtual asUINT GetGlobalFunctionCount() const = 0;

	virtual as_IScriptFunction_t *GetGlobalFunctionByIndex(asUINT index) const = 0;

	virtual as_IScriptFunction_t *GetGlobalFunctionByDecl(const char *declaration) const = 0;

	// Global properties
	virtual int RegisterGlobalProperty(const char *declaration, void *pointer) = 0;

	virtual asUINT GetGlobalPropertyCount() const = 0;

	virtual int GetGlobalPropertyByIndex(asUINT index, const char **name, const char **nameSpace = 0, int *typeId = 0,
	                                     bool *isConst = 0, const char **configGroup = 0, void **pointer = 0,
	                                     as_DWORD *accessMask = 0) const = 0;

	virtual int GetGlobalPropertyIndexByName(const char *name) const = 0;

	virtual int GetGlobalPropertyIndexByDecl(const char *decl) const = 0;

	// Object types
	virtual int RegisterObjectType(const char *obj, int byteSize, as_DWORD flags) = 0;

	virtual int
	RegisterObjectProperty(const char *obj, const char *declaration, int byteOffset, int compositeOffset = 0,
	                       bool isCompositeIndirect = false) = 0;

	virtual int
	RegisterObjectMethod(const char *obj, const char *declaration, const as_SFuncPtr_t &funcPointer, as_DWORD callConv,
	                     void *auxiliary = 0, int compositeOffset = 0, bool isCompositeIndirect = false) = 0;

	virtual int RegisterObjectBehaviour(const char *obj, as_EBehaviours_t behaviour, const char *declaration,
	                                    const as_SFuncPtr_t &funcPointer, as_DWORD callConv, void *auxiliary = 0,
	                                    int compositeOffset = 0, bool isCompositeIndirect = false) = 0;

	virtual int RegisterInterface(const char *name) = 0;

	virtual int RegisterInterfaceMethod(const char *intf, const char *declaration) = 0;

	virtual asUINT GetObjectTypeCount() const = 0;

	virtual as_EBehaviours_t *GetObjectTypeByIndex(asUINT index) const = 0;

	// String factory
	virtual int RegisterStringFactory(const char *datatype, as_IStringFactory_t *factory) = 0;

	virtual int GetStringFactoryReturnTypeId(as_DWORD *flags = 0) const = 0;

	// Default array type
	virtual int RegisterDefaultArrayType(const char *type) = 0;

	virtual int GetDefaultArrayTypeId() const = 0;

	// Enums
	virtual int RegisterEnum(const char *type) = 0;

	virtual int RegisterEnumValue(const char *type, const char *name, int value) = 0;

	virtual asUINT GetEnumCount() const = 0;

	virtual as_EBehaviours_t *GetEnumByIndex(asUINT index) const = 0;

	// Funcdefs
	virtual int RegisterFuncdef(const char *decl) = 0;

	virtual asUINT GetFuncdefCount() const = 0;

	virtual as_EBehaviours_t *GetFuncdefByIndex(asUINT index) const = 0;

	// Typedefs
	virtual int RegisterTypedef(const char *type, const char *decl) = 0;

	virtual asUINT GetTypedefCount() const = 0;

	virtual as_EBehaviours_t *GetTypedefByIndex(asUINT index) const = 0;

	// Configuration groups
	virtual int BeginConfigGroup(const char *groupName) = 0;

	virtual int EndConfigGroup() = 0;

	virtual int RemoveConfigGroup(const char *groupName) = 0;

	virtual as_DWORD SetDefaultAccessMask(as_DWORD defaultMask) = 0;

	virtual int SetDefaultNamespace(const char *nameSpace) = 0;

	virtual const char *GetDefaultNamespace() const = 0;

	// Script modules
	virtual as_IScriptModule_t *GetModule(const char *module, as_EGMFlags_t flag = AS_GM_ONLY_IF_EXISTS) = 0;

	virtual int DiscardModule(const char *module) = 0;

	virtual asUINT GetModuleCount() const = 0;

	virtual as_IScriptModule_t *GetModuleByIndex(asUINT index) const = 0;

	// Script functions
	virtual as_IScriptFunction_t *GetFunctionById(int funcId) const = 0;

	// Type identification
	virtual int GetTypeIdByDecl(const char *decl) const = 0;

	virtual const char *GetTypeDeclaration(int typeId, bool includeNamespace = false) const = 0;

	virtual int GetSizeOfPrimitiveType(int typeId) const = 0;

	virtual as_EBehaviours_t *GetTypeInfoById(int typeId) const = 0;

	virtual as_EBehaviours_t *GetTypeInfoByName(const char *name) const = 0;

	virtual as_EBehaviours_t *GetTypeInfoByDecl(const char *decl) const = 0;

	// Script execution
	virtual as_IScriptContext_t *CreateContext() = 0;

	virtual void *CreateScriptObject(const as_EBehaviours_t *type) = 0;

	virtual void *CreateScriptObjectCopy(void *obj, const as_EBehaviours_t *type) = 0;

	virtual void *CreateUninitializedScriptObject(const as_EBehaviours_t *type) = 0;

	virtual as_IScriptFunction_t *CreateDelegate(as_IScriptFunction_t *func, void *obj) = 0;

	virtual int AssignScriptObject(void *dstObj, void *srcObj, const as_EBehaviours_t *type) = 0;

	virtual void ReleaseScriptObject(void *obj, const as_EBehaviours_t *type) = 0;

	virtual void AddRefScriptObject(void *obj, const as_EBehaviours_t *type) = 0;

	virtual int RefCastObject(void *obj, as_EBehaviours_t *fromType, as_EBehaviours_t *toType, void **newPtr,
	                          bool useOnlyImplicitCast = false) = 0;

	virtual as_ILockableSharedBool_t *GetWeakRefFlagOfScriptObject(void *obj, const as_EBehaviours_t *type) const = 0;

	// Context pooling
	virtual as_IScriptContext_t *RequestContext() = 0;

	virtual void ReturnContext(as_IScriptContext_t *ctx) = 0;

	virtual int SetContextCallbacks(as_REQUESTCONTEXTFUNC_t requestCtx, as_RETURNCONTEXTFUNC_t returnCtx, void *param = 0) = 0;

	// String interpretation
	virtual as_ETokenClass_t ParseToken(const char *string, size_t stringLength = 0, asUINT *tokenLength = 0) const = 0;

	// Garbage collection
	virtual int GarbageCollect(as_DWORD flags = AS_GC_FULL_CYCLE, asUINT numIterations = 1) = 0;

	virtual void
	GetGCStatistics(asUINT *currentSize, asUINT *totalDestroyed = 0, asUINT *totalDetected = 0, asUINT *newObjects = 0,
	                asUINT *totalNewDestroyed = 0) const = 0;

	virtual int NotifyGarbageCollectorOfNewObject(void *obj, as_EBehaviours_t *type) = 0;

	virtual int GetObjectInGC(asUINT idx, asUINT *seqNbr = 0, void **obj = 0, as_EBehaviours_t **type = 0) = 0;

	virtual void GCEnumCallback(void *reference) = 0;

	virtual void ForwardGCEnumReferences(void *ref, as_EBehaviours_t *type) = 0;

	virtual void ForwardGCReleaseReferences(void *ref, as_EBehaviours_t *type) = 0;

	virtual void SetCircularRefDetectedCallback(as_CIRCULARREFFUNC_t callback, void *param = 0) = 0;

	// User data
	virtual void *SetUserData(void *data, asPWORD type = 0) = 0;

	virtual void *GetUserData(asPWORD type = 0) const = 0;

	virtual void SetEngineUserDataCleanupCallback(as_CLEANENGINEFUNC_t callback, asPWORD type = 0) = 0;

	virtual void SetModuleUserDataCleanupCallback(as_CLEANMODULEFUNC_t callback, asPWORD type = 0) = 0;

	virtual void SetContextUserDataCleanupCallback(as_CLEANCONTEXTFUNC_t callback, asPWORD type = 0) = 0;

	virtual void SetFunctionUserDataCleanupCallback(as_CLEANFUNCTIONFUNC_t callback, asPWORD type = 0) = 0;

	virtual void SetTypeInfoUserDataCleanupCallback(as_CLEANTYPEINFOFUNC_t callback, asPWORD type = 0) = 0;

	virtual void SetScriptObjectUserDataCleanupCallback(as_CLEANSCRIPTOBJECTFUNC_t callback, asPWORD type = 0) = 0;

	// Exception handling
	virtual int SetTranslateAppExceptionCallback(as_SFuncPtr_t callback, void *param, int callConv) = 0;

protected:
	virtual ~as_IScriptEngine_t() {}
};

class as_IStringFactory_t {
public:
	virtual const void *GetStringConstant(const char *data, asUINT length) = 0;

	virtual int ReleaseStringConstant(const void *str) = 0;

	virtual int GetRawStringData(const void *str, char *data, asUINT *length) const = 0;

protected:
	virtual ~as_IStringFactory_t() {}
};

class asIThreadManager {
protected:
	virtual ~asIThreadManager() {}
};

class as_IScriptModule_t {
public:
	virtual as_IScriptEngine_t *GetEngine() const = 0;

	virtual void SetName(const char *name) = 0;

	virtual const char *GetName() const = 0;

	virtual void Discard() = 0;

	// Compilation
	virtual int AddScriptSection(const char *name, const char *code, size_t codeLength = 0, int lineOffset = 0) = 0;

	virtual int Build() = 0;

	virtual int CompileFunction(const char *sectionName, const char *code, int lineOffset, as_DWORD compileFlags,
	                            as_IScriptFunction_t **outFunc) = 0;

	virtual int CompileGlobalVar(const char *sectionName, const char *code, int lineOffset) = 0;

	virtual as_DWORD SetAccessMask(as_DWORD accessMask) = 0;

	virtual int SetDefaultNamespace(const char *nameSpace) = 0;

	virtual const char *GetDefaultNamespace() const = 0;

	// Functions
	virtual asUINT GetFunctionCount() const = 0;

	virtual as_IScriptFunction_t *GetFunctionByIndex(asUINT index) const = 0;

	virtual as_IScriptFunction_t *GetFunctionByDecl(const char *decl) const = 0;

	virtual as_IScriptFunction_t *GetFunctionByName(const char *name) const = 0;

	virtual int RemoveFunction(as_IScriptFunction_t *func) = 0;

	// Global variables
	virtual int ResetGlobalVars(as_IScriptContext_t *ctx = 0) = 0;

	virtual asUINT GetGlobalVarCount() const = 0;

	virtual int GetGlobalVarIndexByName(const char *name) const = 0;

	virtual int GetGlobalVarIndexByDecl(const char *decl) const = 0;

	virtual const char *GetGlobalVarDeclaration(asUINT index, bool includeNamespace = false) const = 0;

	virtual int GetGlobalVar(asUINT index, const char **name, const char **nameSpace = 0, int *typeId = 0,
	                         bool *isConst = 0) const = 0;

	virtual void *GetAddressOfGlobalVar(asUINT index) = 0;

	virtual int RemoveGlobalVar(asUINT index) = 0;

	// Type identification
	virtual asUINT GetObjectTypeCount() const = 0;

	virtual as_EBehaviours_t *GetObjectTypeByIndex(asUINT index) const = 0;

	virtual int GetTypeIdByDecl(const char *decl) const = 0;

	virtual as_EBehaviours_t *GetTypeInfoByName(const char *name) const = 0;

	virtual as_EBehaviours_t *GetTypeInfoByDecl(const char *decl) const = 0;

	// Enums
	virtual asUINT GetEnumCount() const = 0;

	virtual as_EBehaviours_t *GetEnumByIndex(asUINT index) const = 0;

	// Typedefs
	virtual asUINT GetTypedefCount() const = 0;

	virtual as_EBehaviours_t *GetTypedefByIndex(asUINT index) const = 0;

	// Dynamic binding between modules
	virtual asUINT GetImportedFunctionCount() const = 0;

	virtual int GetImportedFunctionIndexByDecl(const char *decl) const = 0;

	virtual const char *GetImportedFunctionDeclaration(asUINT importIndex) const = 0;

	virtual const char *GetImportedFunctionSourceModule(asUINT importIndex) const = 0;

	virtual int BindImportedFunction(asUINT importIndex, as_IScriptFunction_t *func) = 0;

	virtual int UnbindImportedFunction(asUINT importIndex) = 0;

	virtual int BindAllImportedFunctions() = 0;

	virtual int UnbindAllImportedFunctions() = 0;

	// Byte code saving and loading
	virtual int SaveByteCode(asIBinaryStream *out, bool stripDebugInfo = false) const = 0;

	virtual int LoadByteCode(asIBinaryStream *in, bool *wasDebugInfoStripped = 0) = 0;

	// User data
	virtual void *SetUserData(void *data, asPWORD type = 0) = 0;

	virtual void *GetUserData(asPWORD type = 0) const = 0;

protected:
	virtual ~as_IScriptModule_t() {}
};

class as_IScriptContext_t {
public:
	// Memory management
	virtual int AddRef() const = 0;

	virtual int Release() const = 0;

	// Miscellaneous
	virtual as_IScriptEngine_t *GetEngine() const = 0;

	// Execution
	virtual int Prepare(as_IScriptFunction_t *func) = 0;

	virtual int Unprepare() = 0;

	virtual int Execute() = 0;

	virtual int Abort() = 0;

	virtual int Suspend() = 0;

	virtual asEContextState GetState() const = 0;

	virtual int PushState() = 0;

	virtual int PopState() = 0;

	virtual bool IsNested(asUINT *nestCount = 0) const = 0;

	// Object pointer for calling class methods
	virtual int SetObject(void *obj) = 0;

	// Arguments
	virtual int SetArgByte(asUINT arg, asBYTE value) = 0;

	virtual int SetArgWord(asUINT arg, asWORD value) = 0;

	virtual int SetArgDWord(asUINT arg, as_DWORD value) = 0;

	virtual int SetArgQWord(asUINT arg, asQWORD value) = 0;

	virtual int SetArgFloat(asUINT arg, float value) = 0;

	virtual int SetArgDouble(asUINT arg, double value) = 0;

	virtual int SetArgAddress(asUINT arg, void *addr) = 0;

	virtual int SetArgObject(asUINT arg, void *obj) = 0;

	virtual int SetArgVarType(asUINT arg, void *ptr, int typeId) = 0;

	virtual void *GetAddressOfArg(asUINT arg) = 0;

	// Return value
	virtual asBYTE GetReturnByte() = 0;

	virtual asWORD GetReturnWord() = 0;

	virtual as_DWORD GetReturnDWord() = 0;

	virtual asQWORD GetReturnQWord() = 0;

	virtual float GetReturnFloat() = 0;

	virtual double GetReturnDouble() = 0;

	virtual void *GetReturnAddress() = 0;

	virtual void *GetReturnObject() = 0;

	virtual void *GetAddressOfReturnValue() = 0;

	// Exception handling
	virtual int SetException(const char *info, bool allowCatch = true) = 0;

	virtual int GetExceptionLineNumber(int *column = 0, const char **sectionName = 0) = 0;

	virtual as_IScriptFunction_t *GetExceptionFunction() = 0;

	virtual const char *GetExceptionString() = 0;

	virtual bool WillExceptionBeCaught() = 0;

	virtual int SetExceptionCallback(as_SFuncPtr_t callback, void *obj, int callConv) = 0;

	virtual void ClearExceptionCallback() = 0;

	// Debugging
	virtual int SetLineCallback(as_SFuncPtr_t callback, void *obj, int callConv) = 0;

	virtual void ClearLineCallback() = 0;

	virtual asUINT GetCallstackSize() const = 0;

	virtual as_IScriptFunction_t *GetFunction(asUINT stackLevel = 0) = 0;

	virtual int GetLineNumber(asUINT stackLevel = 0, int *column = 0, const char **sectionName = 0) = 0;

	virtual int GetVarCount(asUINT stackLevel = 0) = 0;

	virtual const char *GetVarName(asUINT varIndex, asUINT stackLevel = 0) = 0;

	virtual const char *GetVarDeclaration(asUINT varIndex, asUINT stackLevel = 0, bool includeNamespace = false) = 0;

	virtual int GetVarTypeId(asUINT varIndex, asUINT stackLevel = 0) = 0;

	virtual void *GetAddressOfVar(asUINT varIndex, asUINT stackLevel = 0) = 0;

	virtual bool IsVarInScope(asUINT varIndex, asUINT stackLevel = 0) = 0;

	virtual int GetThisTypeId(asUINT stackLevel = 0) = 0;

	virtual void *GetThisPointer(asUINT stackLevel = 0) = 0;

	virtual as_IScriptFunction_t *GetSystemFunction() = 0;

	// User data
	virtual void *SetUserData(void *data, asPWORD type = 0) = 0;

	virtual void *GetUserData(asPWORD type = 0) const = 0;

protected:
	virtual ~as_IScriptContext_t() {}
};

class asIScriptGeneric {
public:
	// Miscellaneous
	virtual as_IScriptEngine_t *GetEngine() const = 0;

	virtual as_IScriptFunction_t *GetFunction() const = 0;

	virtual void *GetAuxiliary() const = 0;

	// Object
	virtual void *GetObject() = 0;

	virtual int GetObjectTypeId() const = 0;

	// Arguments
	virtual int GetArgCount() const = 0;

	virtual int GetArgTypeId(asUINT arg, as_DWORD *flags = 0) const = 0;

	virtual asBYTE GetArgByte(asUINT arg) = 0;

	virtual asWORD GetArgWord(asUINT arg) = 0;

	virtual as_DWORD GetArgDWord(asUINT arg) = 0;

	virtual asQWORD GetArgQWord(asUINT arg) = 0;

	virtual float GetArgFloat(asUINT arg) = 0;

	virtual double GetArgDouble(asUINT arg) = 0;

	virtual void *GetArgAddress(asUINT arg) = 0;

	virtual void *GetArgObject(asUINT arg) = 0;

	virtual void *GetAddressOfArg(asUINT arg) = 0;

	// Return value
	virtual int GetReturnTypeId(as_DWORD *flags = 0) const = 0;

	virtual int SetReturnByte(asBYTE val) = 0;

	virtual int SetReturnWord(asWORD val) = 0;

	virtual int SetReturnDWord(as_DWORD val) = 0;

	virtual int SetReturnQWord(asQWORD val) = 0;

	virtual int SetReturnFloat(float val) = 0;

	virtual int SetReturnDouble(double val) = 0;

	virtual int SetReturnAddress(void *addr) = 0;

	virtual int SetReturnObject(void *obj) = 0;

	virtual void *GetAddressOfReturnLocation() = 0;

protected:
	virtual ~asIScriptGeneric() {}
};

class asIScriptObject {
public:
	// Memory management
	virtual int AddRef() const = 0;

	virtual int Release() const = 0;

	virtual as_ILockableSharedBool_t *GetWeakRefFlag() const = 0;

	// Type info
	virtual int GetTypeId() const = 0;

	virtual as_EBehaviours_t *GetObjectType() const = 0;

	// Class properties
	virtual asUINT GetPropertyCount() const = 0;

	virtual int GetPropertyTypeId(asUINT prop) const = 0;

	virtual const char *GetPropertyName(asUINT prop) const = 0;

	virtual void *GetAddressOfProperty(asUINT prop) = 0;

	// Miscellaneous
	virtual as_IScriptEngine_t *GetEngine() const = 0;

	virtual int CopyFrom(const asIScriptObject *other) = 0;

	// User data
	virtual void *SetUserData(void *data, asPWORD type = 0) = 0;

	virtual void *GetUserData(asPWORD type = 0) const = 0;

protected:
	virtual ~asIScriptObject() {}
};

class as_EBehaviours_t {
public:
	// Miscellaneous
	virtual as_IScriptEngine_t *GetEngine() const = 0;

	virtual const char *GetConfigGroup() const = 0;

	virtual as_DWORD GetAccessMask() const = 0;

	virtual as_IScriptModule_t *GetModule() const = 0;

	// Memory management
	virtual int AddRef() const = 0;

	virtual int Release() const = 0;

	// Type info
	virtual const char *GetName() const = 0;

	virtual const char *GetNamespace() const = 0;

	virtual as_EBehaviours_t *GetBaseType() const = 0;

	virtual bool DerivesFrom(const as_EBehaviours_t *objType) const = 0;

	virtual as_DWORD GetFlags() const = 0;

	virtual asUINT GetSize() const = 0;

	virtual int GetTypeId() const = 0;

	virtual int GetSubTypeId(asUINT subTypeIndex = 0) const = 0;

	virtual as_EBehaviours_t *GetSubType(asUINT subTypeIndex = 0) const = 0;

	virtual asUINT GetSubTypeCount() const = 0;

	// Interfaces
	virtual asUINT GetInterfaceCount() const = 0;

	virtual as_EBehaviours_t *GetInterface(asUINT index) const = 0;

	virtual bool Implements(const as_EBehaviours_t *objType) const = 0;

	// Factories
	virtual asUINT GetFactoryCount() const = 0;

	virtual as_IScriptFunction_t *GetFactoryByIndex(asUINT index) const = 0;

	virtual as_IScriptFunction_t *GetFactoryByDecl(const char *decl) const = 0;

	// Methods
	virtual asUINT GetMethodCount() const = 0;

	virtual as_IScriptFunction_t *GetMethodByIndex(asUINT index, bool getVirtual = true) const = 0;

	virtual as_IScriptFunction_t *GetMethodByName(const char *name, bool getVirtual = true) const = 0;

	virtual as_IScriptFunction_t *GetMethodByDecl(const char *decl, bool getVirtual = true) const = 0;

	// Properties
	virtual asUINT GetPropertyCount() const = 0;

	virtual int
	GetProperty(asUINT index, const char **name, int *typeId = 0, bool *isPrivate = 0, bool *isProtected = 0,
	            int *offset = 0, bool *isReference = 0, as_DWORD *accessMask = 0, int *compositeOffset = 0,
	            bool *isCompositeIndirect = 0) const = 0;

	virtual const char *GetPropertyDeclaration(asUINT index, bool includeNamespace = false) const = 0;

	// Behaviours
	virtual asUINT GetBehaviourCount() const = 0;

	virtual as_IScriptFunction_t *GetBehaviourByIndex(asUINT index, as_EBehaviours_t *outBehaviour) const = 0;

	// Child types
	virtual asUINT GetChildFuncdefCount() const = 0;

	virtual as_EBehaviours_t *GetChildFuncdef(asUINT index) const = 0;

	virtual as_EBehaviours_t *GetParentType() const = 0;

	// Enums
	virtual asUINT GetEnumValueCount() const = 0;

	virtual const char *GetEnumValueByIndex(asUINT index, int *outValue) const = 0;

	// Typedef
	virtual int GetTypedefTypeId() const = 0;

	// Funcdef
	virtual as_IScriptFunction_t *GetFuncdefSignature() const = 0;

	// User data
	virtual void *SetUserData(void *data, asPWORD type = 0) = 0;

	virtual void *GetUserData(asPWORD type = 0) const = 0;

protected:
	virtual ~as_EBehaviours_t() {}
};

class as_IScriptFunction_t {
public:
	virtual as_IScriptEngine_t *GetEngine() const = 0;

	// Memory management
	virtual int AddRef() const = 0;

	virtual int Release() const = 0;

	// Miscellaneous
	virtual int GetId() const = 0;

	virtual asEFuncType GetFuncType() const = 0;

	virtual const char *GetModuleName() const = 0;

	virtual as_IScriptModule_t *GetModule() const = 0;

	virtual const char *GetScriptSectionName() const = 0;

	virtual const char *GetConfigGroup() const = 0;

	virtual as_DWORD GetAccessMask() const = 0;

	virtual void *GetAuxiliary() const = 0;

	// Function signature
	virtual as_EBehaviours_t *GetObjectType() const = 0;

	virtual const char *GetObjectName() const = 0;

	virtual const char *GetName() const = 0;

	virtual const char *GetNamespace() const = 0;

	virtual const char *GetDeclaration(bool includeObjectName = true, bool includeNamespace = false,
	                                   bool includeParamNames = false) const = 0;

	virtual bool IsReadOnly() const = 0;

	virtual bool IsPrivate() const = 0;

	virtual bool IsProtected() const = 0;

	virtual bool IsFinal() const = 0;

	virtual bool IsOverride() const = 0;

	virtual bool IsShared() const = 0;

	virtual bool IsExplicit() const = 0;

	virtual bool IsProperty() const = 0;

	virtual asUINT GetParamCount() const = 0;

	virtual int GetParam(asUINT index, int *typeId, as_DWORD *flags = 0, const char **name = 0,
	                     const char **defaultArg = 0) const = 0;

	virtual int GetReturnTypeId(as_DWORD *flags = 0) const = 0;

	// Type id for function pointers
	virtual int GetTypeId() const = 0;

	virtual bool IsCompatibleWithTypeId(int typeId) const = 0;

	// Delegates
	virtual void *GetDelegateObject() const = 0;

	virtual as_EBehaviours_t *GetDelegateObjectType() const = 0;

	virtual as_IScriptFunction_t *GetDelegateFunction() const = 0;

	// Debug information
	virtual asUINT GetVarCount() const = 0;

	virtual int GetVar(asUINT index, const char **name, int *typeId = 0) const = 0;

	virtual const char *GetVarDecl(asUINT index, bool includeNamespace = false) const = 0;

	virtual int FindNextLineWithCode(int line) const = 0;

	// For JIT compilation
	virtual as_DWORD *GetByteCode(asUINT *length = 0) = 0;

	// User data
	virtual void *SetUserData(void *userData, asPWORD type = 0) = 0;

	virtual void *GetUserData(asPWORD type = 0) const = 0;

protected:
	virtual ~as_IScriptFunction_t() {};
};

class asIBinaryStream {
public:
	virtual int Read(void *ptr, asUINT size) = 0;

	virtual int Write(const void *ptr, asUINT size) = 0;

public:
	virtual ~asIBinaryStream() {}
};

class as_ILockableSharedBool_t {
public:
	// Memory management
	virtual int AddRef() const = 0;

	virtual int Release() const = 0;

	// Value
	virtual bool Get() const = 0;

	virtual void Set(bool val) = 0;

	// Thread management
	virtual void Lock() const = 0;

	virtual void Unlock() const = 0;

protected:
	virtual ~as_ILockableSharedBool_t() {}
};

//-----------------------------------------------------------------
// Function pointers

// Template function to capture all global functions,
// except the ones using the generic calling convention
template<class T>
inline as_SFuncPtr_t asFunctionPtr(T func) {
	// Mark this as a global function
	as_SFuncPtr_t p(2);

#ifdef AS_64BIT_PTR
	// The size_t cast is to avoid a compiler warning with asFUNCTION(0)
	// on 64bit, as 0 is interpreted as a 32bit int value
	p.ptr.f.func = reinterpret_cast<asFUNCTION_t>(size_t(func));
#else
	// MSVC6 doesn't like the size_t cast above so I
	// solved this with a separate code for 32bit.
	p.ptr.f.func = reinterpret_cast<asFUNCTION_t>(func);
#endif

	return p;
}

// Specialization for functions using the generic calling convention
template<>
inline as_SFuncPtr_t asFunctionPtr<asGENFUNC_t>(asGENFUNC_t func) {
	// Mark this as a generic function
	as_SFuncPtr_t p(1);
	p.ptr.f.func = reinterpret_cast<asFUNCTION_t>(func);
	return p;
}

#ifndef AS_NO_CLASS_METHODS

// Method pointers

// Declare a dummy class so that we can determine the size of a simple method pointer
class asCSimpleDummy {
};
typedef void (asCSimpleDummy::*asSIMPLEMETHOD_t)();
const int SINGLE_PTR_SIZE = sizeof(asSIMPLEMETHOD_t);

// Define template
template<int N>
struct asSMethodPtr {
	template<class M>
	static as_SFuncPtr_t Convert(M Mthd) {
		// This version of the function should never be executed, nor compiled,
		// as it would mean that the size of the method pointer cannot be determined.

		int ERROR_UnsupportedMethodPtr[N - 100];

		as_SFuncPtr_t p(0);
		return p;
	}
};

// Template specialization
template<>
struct asSMethodPtr<SINGLE_PTR_SIZE> {
	template<class M>
	static as_SFuncPtr_t Convert(M Mthd) {
		// Mark this as a class method
		as_SFuncPtr_t p(3);
		p.CopyMethodPtr(&Mthd, SINGLE_PTR_SIZE);
		return p;
	}
};

#if defined(_MSC_VER) && !defined(__MWERKS__)

// MSVC and Intel uses different sizes for different class method pointers
template<>
struct asSMethodPtr<SINGLE_PTR_SIZE + 1 * sizeof(int)> {
	template<class M>
	static as_SFuncPtr_t Convert(M Mthd) {
		// Mark this as a class method
		as_SFuncPtr_t p(3);
		p.CopyMethodPtr(&Mthd, SINGLE_PTR_SIZE + sizeof(int));
		return p;
	}
};

template<>
struct asSMethodPtr<SINGLE_PTR_SIZE + 2 * sizeof(int)> {
	template<class M>
	static as_SFuncPtr_t Convert(M Mthd) {
		// On 32bit platforms with is where a class with virtual inheritance falls.
		// On 64bit platforms we can also fall here if 8byte data alignments is used.

		// Mark this as a class method
		as_SFuncPtr_t p(3);
		p.CopyMethodPtr(&Mthd, SINGLE_PTR_SIZE + 2 * sizeof(int));

		// Microsoft has a terrible optimization on class methods with virtual inheritance.
		// They are hardcoding an important offset, which is not coming in the method pointer.

#if defined(_MSC_VER) && !defined(AS_64BIT_PTR)
		// Method pointers for virtual inheritance is not supported,
			// as it requires the location of the vbase table, which is
			// only available to the C++ compiler, but not in the method
			// pointer.

			// You can get around this by forward declaring the class and
			// storing the sizeof its method pointer in a constant. Example:

			// class ClassWithVirtualInheritance;
			// const int ClassWithVirtualInheritance_workaround = sizeof(void ClassWithVirtualInheritance::*());

			// This will force the compiler to use the unknown type
			// for the class, which falls under the next case


			// Copy the virtual table index to the 4th dword so that AngelScript
			// can properly detect and deny the use of methods with virtual inheritance.
			*(reinterpret_cast<asDWORD*>(&p)+3) = *(reinterpret_cast<asDWORD*>(&p)+2);
#endif

		return p;
	}
};

template<>
struct asSMethodPtr<SINGLE_PTR_SIZE + 3 * sizeof(int)> {
	template<class M>
	static as_SFuncPtr_t Convert(M Mthd) {
		// Mark this as a class method
		as_SFuncPtr_t p(3);
		p.CopyMethodPtr(&Mthd, SINGLE_PTR_SIZE + 3 * sizeof(int));
		return p;
	}
};

template<>
struct asSMethodPtr<SINGLE_PTR_SIZE + 4 * sizeof(int)> {
	template<class M>
	static as_SFuncPtr_t Convert(M Mthd) {
		// On 64bit platforms with 8byte data alignment
		// the unknown class method pointers will come here.

		// Mark this as a class method
		as_SFuncPtr_t p(3);
		p.CopyMethodPtr(&Mthd, SINGLE_PTR_SIZE + 4 * sizeof(int));
		return p;
	}
};

#endif

#endif // AS_NO_CLASS_METHODS

//----------------------------------------------------------------
// JIT compiler

typedef struct as_SVMRegisters {
	as_DWORD *programPointer;     // points to current bytecode instruction
	as_DWORD *stackFramePointer;  // function stack frame
	as_DWORD *stackPointer;       // top of stack (grows downward)
	asQWORD valueRegister;      // temp register for primitives
	void *objectRegister;     // temp register for objects and handles
	as_ITypeInfo_t *objectType;      // type of object held in object register
	bool doProcessSuspend;   // whether or not the JIT should break out when it encounters a suspend instruction
	as_IScriptContext_t *ctx;             // the active context
} as_SVMRegisters_t;

typedef void ( *as_JITFunction_t )(as_SVMRegisters_t *registers, asPWORD jitArg);

class as_IJITCompiler_t {
public:
	virtual int CompileFunction(as_IScriptFunction_t *function, as_JITFunction_t *output) = 0;

	virtual void ReleaseJITFunction(as_JITFunction_t func) = 0;

public:
	virtual ~as_IJITCompiler_t() {}
};

// Byte code instructions
typedef enum as_EBCInstr {
	AS_BC_PopPtr = 0,
	AS_BC_PshGPtr = 1,
	AS_BC_PshC4 = 2,
	AS_BC_PshV4 = 3,
	AS_BC_PSF = 4,
	AS_BC_SwapPtr = 5,
	AS_BC_NOT = 6,
	AS_BC_PshG4 = 7,
	AS_BC_LdGRdR4 = 8,
	AS_BC_CALL = 9,
	AS_BC_RET = 10,
	AS_BC_JMP = 11,
	AS_BC_JZ = 12,
	AS_BC_JNZ = 13,
	AS_BC_JS = 14,
	AS_BC_JNS = 15,
	AS_BC_JP = 16,
	AS_BC_JNP = 17,
	AS_BC_TZ = 18,
	AS_BC_TNZ = 19,
	AS_BC_TS = 20,
	AS_BC_TNS = 21,
	AS_BC_TP = 22,
	AS_BC_TNP = 23,
	AS_BC_NEGi = 24,
	AS_BC_NEGf = 25,
	AS_BC_NEGd = 26,
	AS_BC_INCi16 = 27,
	AS_BC_INCi8 = 28,
	AS_BC_DECi16 = 29,
	AS_BC_DECi8 = 30,
	AS_BC_INCi = 31,
	AS_BC_DECi = 32,
	AS_BC_INCf = 33,
	AS_BC_DECf = 34,
	AS_BC_INCd = 35,
	AS_BC_DECd = 36,
	AS_BC_IncVi = 37,
	AS_BC_DecVi = 38,
	AS_BC_BNOT = 39,
	AS_BC_BAND = 40,
	AS_BC_BOR = 41,
	AS_BC_BXOR = 42,
	AS_BC_BSLL = 43,
	AS_BC_BSRL = 44,
	AS_BC_BSRA = 45,
	AS_BC_COPY = 46,
	AS_BC_PshC8 = 47,
	AS_BC_PshVPtr = 48,
	AS_BC_RDSPtr = 49,
	AS_BC_CMPd = 50,
	AS_BC_CMPu = 51,
	AS_BC_CMPf = 52,
	AS_BC_CMPi = 53,
	AS_BC_CMPIi = 54,
	AS_BC_CMPIf = 55,
	AS_BC_CMPIu = 56,
	AS_BC_JMPP = 57,
	AS_BC_PopRPtr = 58,
	AS_BC_PshRPtr = 59,
	AS_BC_STR = 60,
	AS_BC_CALLSYS = 61,
	AS_BC_CALLBND = 62,
	AS_BC_SUSPEND = 63,
	AS_BC_ALLOC = 64,
	AS_BC_FREE = 65,
	AS_BC_LOADOBJ = 66,
	AS_BC_STOREOBJ = 67,
	AS_BC_GETOBJ = 68,
	AS_BC_REFCPY = 69,
	AS_BC_CHKREF = 70,
	AS_BC_GETOBJREF = 71,
	AS_BC_GETREF = 72,
	AS_BC_PshNull = 73,
	AS_BC_ClrVPtr = 74,
	AS_BC_OBJTYPE = 75,
	AS_BC_TYPEID = 76,
	AS_BC_SetV4 = 77,
	AS_BC_SetV8 = 78,
	AS_BC_ADDSi = 79,
	AS_BC_CpyVtoV4 = 80,
	AS_BC_CpyVtoV8 = 81,
	AS_BC_CpyVtoR4 = 82,
	AS_BC_CpyVtoR8 = 83,
	AS_BC_CpyVtoG4 = 84,
	AS_BC_CpyRtoV4 = 85,
	AS_BC_CpyRtoV8 = 86,
	AS_BC_CpyGtoV4 = 87,
	AS_BC_WRTV1 = 88,
	AS_BC_WRTV2 = 89,
	AS_BC_WRTV4 = 90,
	AS_BC_WRTV8 = 91,
	AS_BC_RDR1 = 92,
	AS_BC_RDR2 = 93,
	AS_BC_RDR4 = 94,
	AS_BC_RDR8 = 95,
	AS_BC_LDG = 96,
	AS_BC_LDV = 97,
	AS_BC_PGA = 98,
	AS_BC_CmpPtr = 99,
	AS_BC_VAR = 100,
	AS_BC_iTOf = 101,
	AS_BC_fTOi = 102,
	AS_BC_uTOf = 103,
	AS_BC_fTOu = 104,
	AS_BC_sbTOi = 105,
	AS_BC_swTOi = 106,
	AS_BC_ubTOi = 107,
	AS_BC_uwTOi = 108,
	AS_BC_dTOi = 109,
	AS_BC_dTOu = 110,
	AS_BC_dTOf = 111,
	AS_BC_iTOd = 112,
	AS_BC_uTOd = 113,
	AS_BC_fTOd = 114,
	AS_BC_ADDi = 115,
	AS_BC_SUBi = 116,
	AS_BC_MULi = 117,
	AS_BC_DIVi = 118,
	AS_BC_MODi = 119,
	AS_BC_ADDf = 120,
	AS_BC_SUBf = 121,
	AS_BC_MULf = 122,
	AS_BC_DIVf = 123,
	AS_BC_MODf = 124,
	AS_BC_ADDd = 125,
	AS_BC_SUBd = 126,
	AS_BC_MULd = 127,
	AS_BC_DIVd = 128,
	AS_BC_MODd = 129,
	AS_BC_ADDIi = 130,
	AS_BC_SUBIi = 131,
	AS_BC_MULIi = 132,
	AS_BC_ADDIf = 133,
	AS_BC_SUBIf = 134,
	AS_BC_MULIf = 135,
	AS_BC_SetG4 = 136,
	AS_BC_ChkRefS = 137,
	AS_BC_ChkNullV = 138,
	AS_BC_CALLINTF = 139,
	AS_BC_iTOb = 140,
	AS_BC_iTOw = 141,
	AS_BC_SetV1 = 142,
	AS_BC_SetV2 = 143,
	AS_BC_Cast = 144,
	AS_BC_i64TOi = 145,
	AS_BC_uTOi64 = 146,
	AS_BC_iTOi64 = 147,
	AS_BC_fTOi64 = 148,
	AS_BC_dTOi64 = 149,
	AS_BC_fTOu64 = 150,
	AS_BC_dTOu64 = 151,
	AS_BC_i64TOf = 152,
	AS_BC_u64TOf = 153,
	AS_BC_i64TOd = 154,
	AS_BC_u64TOd = 155,
	AS_BC_NEGi64 = 156,
	AS_BC_INCi64 = 157,
	AS_BC_DECi64 = 158,
	AS_BC_BNOT64 = 159,
	AS_BC_ADDi64 = 160,
	AS_BC_SUBi64 = 161,
	AS_BC_MULi64 = 162,
	AS_BC_DIVi64 = 163,
	AS_BC_MODi64 = 164,
	AS_BC_BAND64 = 165,
	AS_BC_BOR64 = 166,
	AS_BC_BXOR64 = 167,
	AS_BC_BSLL64 = 168,
	AS_BC_BSRL64 = 169,
	AS_BC_BSRA64 = 170,
	AS_BC_CMPi64 = 171,
	AS_BC_CMPu64 = 172,
	AS_BC_ChkNullS = 173,
	AS_BC_ClrHi = 174,
	AS_BC_JitEntry = 175,
	AS_BC_CallPtr = 176,
	AS_BC_FuncPtr = 177,
	AS_BC_LoadThisR = 178,
	AS_BC_PshV8 = 179,
	AS_BC_DIVu = 180,
	AS_BC_MODu = 181,
	AS_BC_DIVu64 = 182,
	AS_BC_MODu64 = 183,
	AS_BC_LoadRObjR = 184,
	AS_BC_LoadVObjR = 185,
	AS_BC_RefCpyV = 186,
	AS_BC_JLowZ = 187,
	AS_BC_JLowNZ = 188,
	AS_BC_AllocMem = 189,
	AS_BC_SetListSize = 190,
	AS_BC_PshListElmnt = 191,
	AS_BC_SetListType = 192,
	AS_BC_POWi = 193,
	AS_BC_POWu = 194,
	AS_BC_POWf = 195,
	AS_BC_POWd = 196,
	AS_BC_POWdi = 197,
	AS_BC_POWi64 = 198,
	AS_BC_POWu64 = 199,
	AS_BC_Thiscall1 = 200,
	AS_BC_MAXBYTECODE = 201,

	// Temporary tokens. Can't be output to the final program
	AS_BC_TryBlock = 250,
	AS_BC_VarDecl = 251,
	AS_BC_Block = 252,
	AS_BC_ObjInfo = 253,
	AS_BC_LINE = 254,
	AS_BC_LABEL = 255
} as_EBCInstr_t;

// Instruction types
typedef enum as_EBCType {
	AS_BCTYPE_INFO = 0,
	AS_BCTYPE_NO_ARG = 1,
	AS_BCTYPE_W_ARG = 2,
	AS_BCTYPE_wW_ARG = 3,
	AS_BCTYPE_DW_ARG = 4,
	AS_BCTYPE_rW_DW_ARG = 5,
	AS_BCTYPE_QW_ARG = 6,
	AS_BCTYPE_DW_DW_ARG = 7,
	AS_BCTYPE_wW_rW_rW_ARG = 8,
	AS_BCTYPE_wW_QW_ARG = 9,
	AS_BCTYPE_wW_rW_ARG = 10,
	AS_BCTYPE_rW_ARG = 11,
	AS_BCTYPE_wW_DW_ARG = 12,
	AS_BCTYPE_wW_rW_DW_ARG = 13,
	AS_BCTYPE_rW_rW_ARG = 14,
	AS_BCTYPE_wW_W_ARG = 15,
	AS_BCTYPE_QW_DW_ARG = 16,
	AS_BCTYPE_rW_QW_ARG = 17,
	AS_BCTYPE_W_DW_ARG = 18,
	AS_BCTYPE_rW_W_DW_ARG = 19,
	AS_BCTYPE_rW_DW_DW_ARG = 20
} as_EBCType_t;

// Instruction type sizes
const int asBCTypeSize[21] = {
		0, // AS_BCTYPE_INFO
		1, // AS_BCTYPE_NO_ARG
		1, // AS_BCTYPE_W_ARG
		1, // AS_BCTYPE_wW_ARG
		2, // AS_BCTYPE_DW_ARG
		2, // AS_BCTYPE_rW_DW_ARG
		3, // AS_BCTYPE_QW_ARG
		3, // AS_BCTYPE_DW_DW_ARG
		2, // AS_BCTYPE_wW_rW_rW_ARG
		3, // AS_BCTYPE_wW_QW_ARG
		2, // AS_BCTYPE_wW_rW_ARG
		1, // AS_BCTYPE_rW_ARG
		2, // AS_BCTYPE_wW_DW_ARG
		3, // AS_BCTYPE_wW_rW_DW_ARG
		2, // AS_BCTYPE_rW_rW_ARG
		2, // AS_BCTYPE_wW_W_ARG
		4, // AS_BCTYPE_QW_DW_ARG
		3, // AS_BCTYPE_rW_QW_ARG
		2, // AS_BCTYPE_W_DW_ARG
		3, // AS_BCTYPE_rW_W_DW_ARG
		3  // AS_BCTYPE_rW_DW_DW_ARG
};

// Instruction info
typedef struct as_SBCInfo {
	as_EBCInstr_t bc;
	as_EBCType_t type;
	int stackInc;
	const char *name;
} as_SBCInfo_t;

#ifndef AS_64BIT_PTR
	#define AS_BCTYPE_PTR_ARG    AS_BCTYPE_DW_ARG
	#define AS_BCTYPE_PTR_DW_ARG AS_BCTYPE_DW_DW_ARG
	#define AS_BCTYPE_wW_PTR_ARG AS_BCTYPE_wW_DW_ARG
	#define AS_BCTYPE_rW_PTR_ARG AS_BCTYPE_rW_DW_ARG
	#ifndef AS_PTR_SIZE
		#define AS_PTR_SIZE 1
	#endif
#else
	#define AS_BCTYPE_PTR_ARG    AS_BCTYPE_QW_ARG
	#define AS_BCTYPE_PTR_DW_ARG AS_BCTYPE_QW_DW_ARG
	#define AS_BCTYPE_wW_PTR_ARG AS_BCTYPE_wW_QW_ARG
	#define AS_BCTYPE_rW_PTR_ARG AS_BCTYPE_rW_QW_ARG
	#ifndef AS_PTR_SIZE
		#define AS_PTR_SIZE 2
	#endif
#endif

#define asBCINFO(b, t, s) { AS_BC_##b, AS_BCTYPE_##t, s, #b }
#define asBCINFO_DUMMY(b) { AS_BC_MAXBYTECODE, AS_BCTYPE_INFO, 0, "BC_" #b }

const as_SBCInfo_t asBCInfo[256] = {
		asBCINFO(PopPtr, NO_ARG, -AS_PTR_SIZE),
		asBCINFO(PshGPtr, PTR_ARG, AS_PTR_SIZE),
		asBCINFO(PshC4, DW_ARG, 1),
		asBCINFO(PshV4, rW_ARG, 1),
		asBCINFO(PSF, rW_ARG, AS_PTR_SIZE),
		asBCINFO(SwapPtr, NO_ARG, 0),
		asBCINFO(NOT, rW_ARG, 0),
		asBCINFO(PshG4, PTR_ARG, 1),
		asBCINFO(LdGRdR4, wW_PTR_ARG, 0),
		asBCINFO(CALL, DW_ARG, 0xFFFF),
		asBCINFO(RET, W_ARG, 0xFFFF),
		asBCINFO(JMP, DW_ARG, 0),
		asBCINFO(JZ, DW_ARG, 0),
		asBCINFO(JNZ, DW_ARG, 0),
		asBCINFO(JS, DW_ARG, 0),
		asBCINFO(JNS, DW_ARG, 0),
		asBCINFO(JP, DW_ARG, 0),
		asBCINFO(JNP, DW_ARG, 0),
		asBCINFO(TZ, NO_ARG, 0),
		asBCINFO(TNZ, NO_ARG, 0),
		asBCINFO(TS, NO_ARG, 0),
		asBCINFO(TNS, NO_ARG, 0),
		asBCINFO(TP, NO_ARG, 0),
		asBCINFO(TNP, NO_ARG, 0),
		asBCINFO(NEGi, rW_ARG, 0),
		asBCINFO(NEGf, rW_ARG, 0),
		asBCINFO(NEGd, rW_ARG, 0),
		asBCINFO(INCi16, NO_ARG, 0),
		asBCINFO(INCi8, NO_ARG, 0),
		asBCINFO(DECi16, NO_ARG, 0),
		asBCINFO(DECi8, NO_ARG, 0),
		asBCINFO(INCi, NO_ARG, 0),
		asBCINFO(DECi, NO_ARG, 0),
		asBCINFO(INCf, NO_ARG, 0),
		asBCINFO(DECf, NO_ARG, 0),
		asBCINFO(INCd, NO_ARG, 0),
		asBCINFO(DECd, NO_ARG, 0),
		asBCINFO(IncVi, rW_ARG, 0),
		asBCINFO(DecVi, rW_ARG, 0),
		asBCINFO(BNOT, rW_ARG, 0),
		asBCINFO(BAND, wW_rW_rW_ARG, 0),
		asBCINFO(BOR, wW_rW_rW_ARG, 0),
		asBCINFO(BXOR, wW_rW_rW_ARG, 0),
		asBCINFO(BSLL, wW_rW_rW_ARG, 0),
		asBCINFO(BSRL, wW_rW_rW_ARG, 0),
		asBCINFO(BSRA, wW_rW_rW_ARG, 0),
		asBCINFO(COPY, W_DW_ARG, -AS_PTR_SIZE),
		asBCINFO(PshC8, QW_ARG, 2),
		asBCINFO(PshVPtr, rW_ARG, AS_PTR_SIZE),
		asBCINFO(RDSPtr, NO_ARG, 0),
		asBCINFO(CMPd, rW_rW_ARG, 0),
		asBCINFO(CMPu, rW_rW_ARG, 0),
		asBCINFO(CMPf, rW_rW_ARG, 0),
		asBCINFO(CMPi, rW_rW_ARG, 0),
		asBCINFO(CMPIi, rW_DW_ARG, 0),
		asBCINFO(CMPIf, rW_DW_ARG, 0),
		asBCINFO(CMPIu, rW_DW_ARG, 0),
		asBCINFO(JMPP, rW_ARG, 0),
		asBCINFO(PopRPtr, NO_ARG, -AS_PTR_SIZE),
		asBCINFO(PshRPtr, NO_ARG, AS_PTR_SIZE),
		asBCINFO(STR, W_ARG, 1 + AS_PTR_SIZE),
		asBCINFO(CALLSYS, DW_ARG, 0xFFFF),
		asBCINFO(CALLBND, DW_ARG, 0xFFFF),
		asBCINFO(SUSPEND, NO_ARG, 0),
		asBCINFO(ALLOC, PTR_DW_ARG, 0xFFFF),
		asBCINFO(FREE, wW_PTR_ARG, 0),
		asBCINFO(LOADOBJ, rW_ARG, 0),
		asBCINFO(STOREOBJ, wW_ARG, 0),
		asBCINFO(GETOBJ, W_ARG, 0),
		asBCINFO(REFCPY, PTR_ARG, -AS_PTR_SIZE),
		asBCINFO(CHKREF, NO_ARG, 0),
		asBCINFO(GETOBJREF, W_ARG, 0),
		asBCINFO(GETREF, W_ARG, 0),
		asBCINFO(PshNull, NO_ARG, AS_PTR_SIZE),
		asBCINFO(ClrVPtr, wW_ARG, 0),
		asBCINFO(OBJTYPE, PTR_ARG, AS_PTR_SIZE),
		asBCINFO(TYPEID, DW_ARG, 1),
		asBCINFO(SetV4, wW_DW_ARG, 0),
		asBCINFO(SetV8, wW_QW_ARG, 0),
		asBCINFO(ADDSi, W_DW_ARG, 0),
		asBCINFO(CpyVtoV4, wW_rW_ARG, 0),
		asBCINFO(CpyVtoV8, wW_rW_ARG, 0),
		asBCINFO(CpyVtoR4, rW_ARG, 0),
		asBCINFO(CpyVtoR8, rW_ARG, 0),
		asBCINFO(CpyVtoG4, rW_PTR_ARG, 0),
		asBCINFO(CpyRtoV4, wW_ARG, 0),
		asBCINFO(CpyRtoV8, wW_ARG, 0),
		asBCINFO(CpyGtoV4, wW_PTR_ARG, 0),
		asBCINFO(WRTV1, rW_ARG, 0),
		asBCINFO(WRTV2, rW_ARG, 0),
		asBCINFO(WRTV4, rW_ARG, 0),
		asBCINFO(WRTV8, rW_ARG, 0),
		asBCINFO(RDR1, wW_ARG, 0),
		asBCINFO(RDR2, wW_ARG, 0),
		asBCINFO(RDR4, wW_ARG, 0),
		asBCINFO(RDR8, wW_ARG, 0),
		asBCINFO(LDG, PTR_ARG, 0),
		asBCINFO(LDV, rW_ARG, 0),
		asBCINFO(PGA, PTR_ARG, AS_PTR_SIZE),
		asBCINFO(CmpPtr, rW_rW_ARG, 0),
		asBCINFO(VAR, rW_ARG, AS_PTR_SIZE),
		asBCINFO(iTOf, rW_ARG, 0),
		asBCINFO(fTOi, rW_ARG, 0),
		asBCINFO(uTOf, rW_ARG, 0),
		asBCINFO(fTOu, rW_ARG, 0),
		asBCINFO(sbTOi, rW_ARG, 0),
		asBCINFO(swTOi, rW_ARG, 0),
		asBCINFO(ubTOi, rW_ARG, 0),
		asBCINFO(uwTOi, rW_ARG, 0),
		asBCINFO(dTOi, wW_rW_ARG, 0),
		asBCINFO(dTOu, wW_rW_ARG, 0),
		asBCINFO(dTOf, wW_rW_ARG, 0),
		asBCINFO(iTOd, wW_rW_ARG, 0),
		asBCINFO(uTOd, wW_rW_ARG, 0),
		asBCINFO(fTOd, wW_rW_ARG, 0),
		asBCINFO(ADDi, wW_rW_rW_ARG, 0),
		asBCINFO(SUBi, wW_rW_rW_ARG, 0),
		asBCINFO(MULi, wW_rW_rW_ARG, 0),
		asBCINFO(DIVi, wW_rW_rW_ARG, 0),
		asBCINFO(MODi, wW_rW_rW_ARG, 0),
		asBCINFO(ADDf, wW_rW_rW_ARG, 0),
		asBCINFO(SUBf, wW_rW_rW_ARG, 0),
		asBCINFO(MULf, wW_rW_rW_ARG, 0),
		asBCINFO(DIVf, wW_rW_rW_ARG, 0),
		asBCINFO(MODf, wW_rW_rW_ARG, 0),
		asBCINFO(ADDd, wW_rW_rW_ARG, 0),
		asBCINFO(SUBd, wW_rW_rW_ARG, 0),
		asBCINFO(MULd, wW_rW_rW_ARG, 0),
		asBCINFO(DIVd, wW_rW_rW_ARG, 0),
		asBCINFO(MODd, wW_rW_rW_ARG, 0),
		asBCINFO(ADDIi, wW_rW_DW_ARG, 0),
		asBCINFO(SUBIi, wW_rW_DW_ARG, 0),
		asBCINFO(MULIi, wW_rW_DW_ARG, 0),
		asBCINFO(ADDIf, wW_rW_DW_ARG, 0),
		asBCINFO(SUBIf, wW_rW_DW_ARG, 0),
		asBCINFO(MULIf, wW_rW_DW_ARG, 0),
		asBCINFO(SetG4, PTR_DW_ARG, 0),
		asBCINFO(ChkRefS, NO_ARG, 0),
		asBCINFO(ChkNullV, rW_ARG, 0),
		asBCINFO(CALLINTF, DW_ARG, 0xFFFF),
		asBCINFO(iTOb, rW_ARG, 0),
		asBCINFO(iTOw, rW_ARG, 0),
		asBCINFO(SetV1, wW_DW_ARG, 0),
		asBCINFO(SetV2, wW_DW_ARG, 0),
		asBCINFO(Cast, DW_ARG, -AS_PTR_SIZE),
		asBCINFO(i64TOi, wW_rW_ARG, 0),
		asBCINFO(uTOi64, wW_rW_ARG, 0),
		asBCINFO(iTOi64, wW_rW_ARG, 0),
		asBCINFO(fTOi64, wW_rW_ARG, 0),
		asBCINFO(dTOi64, rW_ARG, 0),
		asBCINFO(fTOu64, wW_rW_ARG, 0),
		asBCINFO(dTOu64, rW_ARG, 0),
		asBCINFO(i64TOf, wW_rW_ARG, 0),
		asBCINFO(u64TOf, wW_rW_ARG, 0),
		asBCINFO(i64TOd, rW_ARG, 0),
		asBCINFO(u64TOd, rW_ARG, 0),
		asBCINFO(NEGi64, rW_ARG, 0),
		asBCINFO(INCi64, NO_ARG, 0),
		asBCINFO(DECi64, NO_ARG, 0),
		asBCINFO(BNOT64, rW_ARG, 0),
		asBCINFO(ADDi64, wW_rW_rW_ARG, 0),
		asBCINFO(SUBi64, wW_rW_rW_ARG, 0),
		asBCINFO(MULi64, wW_rW_rW_ARG, 0),
		asBCINFO(DIVi64, wW_rW_rW_ARG, 0),
		asBCINFO(MODi64, wW_rW_rW_ARG, 0),
		asBCINFO(BAND64, wW_rW_rW_ARG, 0),
		asBCINFO(BOR64, wW_rW_rW_ARG, 0),
		asBCINFO(BXOR64, wW_rW_rW_ARG, 0),
		asBCINFO(BSLL64, wW_rW_rW_ARG, 0),
		asBCINFO(BSRL64, wW_rW_rW_ARG, 0),
		asBCINFO(BSRA64, wW_rW_rW_ARG, 0),
		asBCINFO(CMPi64, rW_rW_ARG, 0),
		asBCINFO(CMPu64, rW_rW_ARG, 0),
		asBCINFO(ChkNullS, W_ARG, 0),
		asBCINFO(ClrHi, NO_ARG, 0),
		asBCINFO(JitEntry, PTR_ARG, 0),
		asBCINFO(CallPtr, rW_ARG, 0xFFFF),
		asBCINFO(FuncPtr, PTR_ARG, AS_PTR_SIZE),
		asBCINFO(LoadThisR, W_DW_ARG, 0),
		asBCINFO(PshV8, rW_ARG, 2),
		asBCINFO(DIVu, wW_rW_rW_ARG, 0),
		asBCINFO(MODu, wW_rW_rW_ARG, 0),
		asBCINFO(DIVu64, wW_rW_rW_ARG, 0),
		asBCINFO(MODu64, wW_rW_rW_ARG, 0),
		asBCINFO(LoadRObjR, rW_W_DW_ARG, 0),
		asBCINFO(LoadVObjR, rW_W_DW_ARG, 0),
		asBCINFO(RefCpyV, wW_PTR_ARG, 0),
		asBCINFO(JLowZ, DW_ARG, 0),
		asBCINFO(JLowNZ, DW_ARG, 0),
		asBCINFO(AllocMem, wW_DW_ARG, 0),
		asBCINFO(SetListSize, rW_DW_DW_ARG, 0),
		asBCINFO(PshListElmnt, rW_DW_ARG, AS_PTR_SIZE),
		asBCINFO(SetListType, rW_DW_DW_ARG, 0),
		asBCINFO(POWi, wW_rW_rW_ARG, 0),
		asBCINFO(POWu, wW_rW_rW_ARG, 0),
		asBCINFO(POWf, wW_rW_rW_ARG, 0),
		asBCINFO(POWd, wW_rW_rW_ARG, 0),
		asBCINFO(POWdi, wW_rW_rW_ARG, 0),
		asBCINFO(POWi64, wW_rW_rW_ARG, 0),
		asBCINFO(POWu64, wW_rW_rW_ARG, 0),
		asBCINFO(Thiscall1, DW_ARG, -AS_PTR_SIZE - 1),

		asBCINFO_DUMMY(201),
		asBCINFO_DUMMY(202),
		asBCINFO_DUMMY(203),
		asBCINFO_DUMMY(204),
		asBCINFO_DUMMY(205),
		asBCINFO_DUMMY(206),
		asBCINFO_DUMMY(207),
		asBCINFO_DUMMY(208),
		asBCINFO_DUMMY(209),
		asBCINFO_DUMMY(210),
		asBCINFO_DUMMY(211),
		asBCINFO_DUMMY(212),
		asBCINFO_DUMMY(213),
		asBCINFO_DUMMY(214),
		asBCINFO_DUMMY(215),
		asBCINFO_DUMMY(216),
		asBCINFO_DUMMY(217),
		asBCINFO_DUMMY(218),
		asBCINFO_DUMMY(219),
		asBCINFO_DUMMY(220),
		asBCINFO_DUMMY(221),
		asBCINFO_DUMMY(222),
		asBCINFO_DUMMY(223),
		asBCINFO_DUMMY(224),
		asBCINFO_DUMMY(225),
		asBCINFO_DUMMY(226),
		asBCINFO_DUMMY(227),
		asBCINFO_DUMMY(228),
		asBCINFO_DUMMY(229),
		asBCINFO_DUMMY(230),
		asBCINFO_DUMMY(231),
		asBCINFO_DUMMY(232),
		asBCINFO_DUMMY(233),
		asBCINFO_DUMMY(234),
		asBCINFO_DUMMY(235),
		asBCINFO_DUMMY(236),
		asBCINFO_DUMMY(237),
		asBCINFO_DUMMY(238),
		asBCINFO_DUMMY(239),
		asBCINFO_DUMMY(240),
		asBCINFO_DUMMY(241),
		asBCINFO_DUMMY(242),
		asBCINFO_DUMMY(243),
		asBCINFO_DUMMY(244),
		asBCINFO_DUMMY(245),
		asBCINFO_DUMMY(246),
		asBCINFO_DUMMY(247),
		asBCINFO_DUMMY(248),
		asBCINFO_DUMMY(249),

		asBCINFO(TryBlock, DW_ARG, 0),
		asBCINFO(VarDecl, W_ARG, 0),
		asBCINFO(Block, INFO, 0),
		asBCINFO(ObjInfo, rW_DW_ARG, 0),
		asBCINFO(LINE, INFO, 0),
		asBCINFO(LABEL, INFO, 0)
};

// Macros to access bytecode instruction arguments
#define asBC_DWORDARG(x)  ( *( ( (asDWORD*) x ) + 1 ) )
#define asBC_INTARG(x)    ( *(int*) ( ( (asDWORD*) x ) + 1 ) )
#define asBC_QWORDARG(x)  ( *(asQWORD*) ( ( (asDWORD*) x ) + 1 ) )
#define asBC_FLOATARG(x)  ( *(float*) ( ( (asDWORD*) x ) + 1 ) )
#define asBC_PTRARG(x)    ( *(asPWORD*) ( ( (asDWORD*) x ) + 1 ) )
#define asBC_WORDARG0(x)  ( *( ( (asWORD*) x ) + 1 ) )
#define asBC_WORDARG1(x)  ( *( ( (asWORD*) x ) + 2 ) )
#define asBC_SWORDARG0(x) ( *( ( (short*) x ) + 1 ) )
#define asBC_SWORDARG1(x) ( *( ( (short*) x ) + 2 ) )
#define asBC_SWORDARG2(x) ( *( ( (short*) x ) + 3 ) )

END_AS_NAMESPACE
#endif // ANGELSCRIPT_C_H