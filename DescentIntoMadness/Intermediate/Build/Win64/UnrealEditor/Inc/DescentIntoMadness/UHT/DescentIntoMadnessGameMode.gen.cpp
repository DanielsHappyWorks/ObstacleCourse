// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DescentIntoMadness/DescentIntoMadnessGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDescentIntoMadnessGameMode() {}
// Cross Module References
	DESCENTINTOMADNESS_API UClass* Z_Construct_UClass_ADescentIntoMadnessGameMode();
	DESCENTINTOMADNESS_API UClass* Z_Construct_UClass_ADescentIntoMadnessGameMode_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_DescentIntoMadness();
// End Cross Module References
	void ADescentIntoMadnessGameMode::StaticRegisterNativesADescentIntoMadnessGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ADescentIntoMadnessGameMode);
	UClass* Z_Construct_UClass_ADescentIntoMadnessGameMode_NoRegister()
	{
		return ADescentIntoMadnessGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ADescentIntoMadnessGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADescentIntoMadnessGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_DescentIntoMadness,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADescentIntoMadnessGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADescentIntoMadnessGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "DescentIntoMadnessGameMode.h" },
		{ "ModuleRelativePath", "DescentIntoMadnessGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADescentIntoMadnessGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADescentIntoMadnessGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ADescentIntoMadnessGameMode_Statics::ClassParams = {
		&ADescentIntoMadnessGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADescentIntoMadnessGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ADescentIntoMadnessGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ADescentIntoMadnessGameMode()
	{
		if (!Z_Registration_Info_UClass_ADescentIntoMadnessGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADescentIntoMadnessGameMode.OuterSingleton, Z_Construct_UClass_ADescentIntoMadnessGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ADescentIntoMadnessGameMode.OuterSingleton;
	}
	template<> DESCENTINTOMADNESS_API UClass* StaticClass<ADescentIntoMadnessGameMode>()
	{
		return ADescentIntoMadnessGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADescentIntoMadnessGameMode);
	ADescentIntoMadnessGameMode::~ADescentIntoMadnessGameMode() {}
	struct Z_CompiledInDeferFile_FID_Users_Daniel_OneDrive___Dundalk_Institute_of_Technology_ObstacleCourse_DescentIntoMadness_Source_DescentIntoMadness_DescentIntoMadnessGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Daniel_OneDrive___Dundalk_Institute_of_Technology_ObstacleCourse_DescentIntoMadness_Source_DescentIntoMadness_DescentIntoMadnessGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ADescentIntoMadnessGameMode, ADescentIntoMadnessGameMode::StaticClass, TEXT("ADescentIntoMadnessGameMode"), &Z_Registration_Info_UClass_ADescentIntoMadnessGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADescentIntoMadnessGameMode), 3876002043U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Daniel_OneDrive___Dundalk_Institute_of_Technology_ObstacleCourse_DescentIntoMadness_Source_DescentIntoMadness_DescentIntoMadnessGameMode_h_1968255255(TEXT("/Script/DescentIntoMadness"),
		Z_CompiledInDeferFile_FID_Users_Daniel_OneDrive___Dundalk_Institute_of_Technology_ObstacleCourse_DescentIntoMadness_Source_DescentIntoMadness_DescentIntoMadnessGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Daniel_OneDrive___Dundalk_Institute_of_Technology_ObstacleCourse_DescentIntoMadness_Source_DescentIntoMadness_DescentIntoMadnessGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
