/*
 * windowerhelper_jni.cpp
 * 
 * Copyright © 2012 Windower Team
 */

#include "windowerhelper_jni.h"

#define WINDOWER_HELPER_NO_CLASSES

#include <windowerhelper.h>

#include <jni.h>

extern "C"
{
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1create(JNIEnv* env, jclass, jlongArray result, jint process)
	{
		jlong result_buffer = 0;
		unsigned int error = ::windower_create(reinterpret_cast<windower_instance*>(&result_buffer), process);
		if (!error)
		{
			env->SetLongArrayRegion(result, 0, 1, &result_buffer);
		}
		return error;
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1create_1remote(JNIEnv* env, jclass, jlongArray result, jbyteArray domain, jint process)
	{
		jlong result_buffer = 0;
		jbyte* domain_buffer = env->GetByteArrayElements(domain, 0);
		unsigned int error = ::windower_create_remote(reinterpret_cast<windower_instance*>(&result_buffer), reinterpret_cast<char*>(domain_buffer), process);
		env->ReleaseByteArrayElements(domain, domain_buffer, JNI_ABORT);
		if (!error)
		{
			env->SetLongArrayRegion(result, 0, 1, &result_buffer);
		}
		return error;
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1delete(JNIEnv*, jclass, jlong handle)
	{
		return ::windower_delete(reinterpret_cast<windower_instance>(handle));
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1get_1version(JNIEnv* env, jclass, jlong handle, jintArray result)
	{
		jint result_buffer = 0;
		unsigned int error = ::windower_get_version(reinterpret_cast<windower_instance>(handle), reinterpret_cast<unsigned int*>(&result_buffer));
		if (!error)
		{
			env->SetIntArrayRegion(result, 0, 1, &result_buffer);
		}
		return error;
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1send_1string(JNIEnv* env, jclass, jlong handle, jbyteArray string)
	{
		jbyte* string_buffer = env->GetByteArrayElements(string, 0);
		unsigned int error = ::windower_send_string(reinterpret_cast<windower_instance>(handle), reinterpret_cast<char*>(string_buffer));
		env->ReleaseByteArrayElements(string, string_buffer, JNI_ABORT);
		return error;
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1set_1key_1state(JNIEnv*, jclass, jlong handle, jint x, jint y)
	{
		return ::windower_set_key_state(reinterpret_cast<windower_instance>(handle), x, y);
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1block(JNIEnv*, jclass, jlong handle, jint input_kind)
	{
		return ::windower_block(reinterpret_cast<windower_instance>(handle), input_kind);
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1unblock(JNIEnv*, jclass, jlong handle, jint input_kind)
	{
		return ::windower_unblock(reinterpret_cast<windower_instance>(handle), input_kind);
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1next_1command(JNIEnv* env, jclass, jlong handle, jlongArray result)
	{
		jlong result_buffer = 0;
		unsigned int error = ::windower_next_command(reinterpret_cast<windower_instance>(handle), reinterpret_cast<windower_command*>(&result_buffer));
		if (!error)
		{
			env->SetLongArrayRegion(result, 0, 1, &result_buffer);
		}
		return error;
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1command_1delete(JNIEnv*, jclass, jlong handle)
	{
		return ::windower_command_delete(reinterpret_cast<windower_command>(handle));
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1command_1length(JNIEnv* env, jclass, jlong handle, jintArray result)
	{
		jint result_buffer = 0;
		unsigned int error = ::windower_command_length(reinterpret_cast<windower_command>(handle), reinterpret_cast<unsigned int*>(&result_buffer));
		if (!error)
		{
			env->SetIntArrayRegion(result, 0, 1, &result_buffer);
		}
		return error;
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1command_1string(JNIEnv* env, jclass, jlong handle, jbyteArray result)
	{
		jbyte const* result_buffer = 0;
		unsigned int error = ::windower_command_string(reinterpret_cast<windower_command>(handle), reinterpret_cast<char const**>(&result_buffer));
		if (!error)
		{
			jsize length = env->GetArrayLength(result);
			env->SetByteArrayRegion(result, 0, length, result_buffer);
		}
		return error;
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1create(JNIEnv*env, jclass, jlong handle, jlongArray result, jbyteArray name)
	{
		jlong result_buffer = 0;
		jbyte* name_buffer = env->GetByteArrayElements(name, 0);
		unsigned int error = ::windower_text_create(reinterpret_cast<windower_instance>(handle), reinterpret_cast<windower_text*>(result_buffer), reinterpret_cast<char*>(name_buffer));
		env->ReleaseByteArrayElements(name, name_buffer, JNI_ABORT);
		if (!error)
		{
			env->SetLongArrayRegion(result, 0, 1, &result_buffer);
		}
		return error;
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1delete(JNIEnv*, jclass, jlong handle)
	{
		return ::windower_text_delete(reinterpret_cast<windower_text>(handle));
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1text(JNIEnv* env, jclass, jlong handle, jbyteArray text)
	{
		jbyte* text_buffer = env->GetByteArrayElements(text, 0);
		unsigned int error = ::windower_text_set_text(reinterpret_cast<windower_text>(handle), reinterpret_cast<char*>(text_buffer));
		env->ReleaseByteArrayElements(text, text_buffer, JNI_ABORT);
		return error;
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1show(JNIEnv*, jclass, jlong handle)
	{
		return ::windower_text_show(reinterpret_cast<windower_text>(handle));
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1hide(JNIEnv*, jclass, jlong handle)
	{
		return ::windower_text_hide(reinterpret_cast<windower_text>(handle));
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1location(JNIEnv*, jclass, jlong handle, jint x, jint y)
	{
		return ::windower_text_set_location(reinterpret_cast<windower_text>(handle), x, y);
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1foreground(JNIEnv*, jclass, jlong handle, jbyte red, jbyte green, jbyte blue, jbyte alpha)
	{
		return ::windower_text_set_foreground(reinterpret_cast<windower_text>(handle), red, green, blue, alpha);
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1background(JNIEnv*, jclass, jlong handle, jbyte red, jbyte green, jbyte blue, jbyte alpha)
	{
		return ::windower_text_set_background(reinterpret_cast<windower_text>(handle), red, green, blue, alpha);
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1show_1background(JNIEnv*, jclass, jlong handle)
	{
		return ::windower_text_show_background(reinterpret_cast<windower_text>(handle));
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1hide_1background(JNIEnv*, jclass, jlong handle)
	{
		return ::windower_text_hide_background(reinterpret_cast<windower_text>(handle));
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1font(JNIEnv* env, jclass, jlong handle, jbyteArray typeface, jfloat size)
	{
		jbyte* typeface_buffer = env->GetByteArrayElements(typeface, 0);
		unsigned int error = ::windower_text_set_font(reinterpret_cast<windower_text>(handle), reinterpret_cast<char*>(typeface_buffer), size);
		env->ReleaseByteArrayElements(typeface, typeface_buffer, JNI_ABORT);
		return error;
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1weight(JNIEnv*, jclass, jlong handle, jint weight)
	{
		return ::windower_text_set_weight(reinterpret_cast<windower_text>(handle), weight);
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1style(JNIEnv*, jclass, jlong handle, jint style)
	{
		return ::windower_text_set_style(reinterpret_cast<windower_text>(handle), style);
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1alignment(JNIEnv*, jclass, jlong handle, jint alignment)
	{
		return ::windower_text_set_alignment(reinterpret_cast<windower_text>(handle), alignment);
	}

	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1padding(JNIEnv*, jclass, jlong handle, jfloat pixels)
	{
		return ::windower_text_set_padding(reinterpret_cast<windower_text>(handle), pixels);
	}
}