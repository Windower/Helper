#ifndef WINDOWERHELPER_JNI_H
#define WINDOWERHELPER_JNI_H

/*
 * windowerhelper_jni.h
 * 
 * Copyright © 2012 Windower Team
 */

#pragma once

#include <jni.h>

#ifdef __cplusplus
extern "C"
{
#endif
	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_create
	 * Signature: ([JI)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1create(JNIEnv*, jclass, jlongArray, jint);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_create_remote
	 * Signature: ([J[BI)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1create_1remote(JNIEnv*, jclass, jlongArray, jbyteArray, jint);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_delete
	 * Signature: (J)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1delete(JNIEnv*, jclass, jlong);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_get_version
	 * Signature: (J[I)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1get_1version(JNIEnv*, jclass, jlong, jintArray);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_send_string
	 * Signature: (J[B)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1send_1string(JNIEnv*, jclass, jlong, jbyteArray);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_set_key_state
	 * Signature: (JII)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1set_1key_1state(JNIEnv*, jclass, jlong, jint, jint);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_block
	 * Signature: (JI)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1block(JNIEnv*, jclass, jlong, jint);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_unblock
	 * Signature: (JI)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1unblock(JNIEnv*, jclass, jlong, jint);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_next_command
	 * Signature: (J[J)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1next_1command(JNIEnv*, jclass, jlong, jlongArray);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_command_delete
	 * Signature: (J)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1command_1delete(JNIEnv*, jclass, jlong);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_command_length
	 * Signature: (J[I)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1command_1length(JNIEnv*, jclass, jlong, jintArray);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_command_string
	 * Signature: (J[B)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1command_1string(JNIEnv*, jclass, jlong, jbyteArray);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_create
	 * Signature: (J[J[B)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1create(JNIEnv*, jclass, jlong, jlongArray, jbyteArray);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_delete
	 * Signature: (J)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1delete(JNIEnv*, jclass, jlong);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_set_text
	 * Signature: (J[B)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1text(JNIEnv*, jclass, jlong, jbyteArray);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_show
	 * Signature: (J)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1show(JNIEnv*, jclass, jlong);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_hide
	 * Signature: (J)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1hide(JNIEnv*, jclass, jlong);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_set_location
	 * Signature: (JII)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1location(JNIEnv*, jclass, jlong, jint, jint);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_set_foreground
	 * Signature: (JBBBB)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1foreground(JNIEnv*, jclass, jlong, jbyte, jbyte, jbyte, jbyte);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_set_background
	 * Signature: (JBBBB)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1background(JNIEnv*, jclass, jlong, jbyte, jbyte, jbyte, jbyte);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_show_background
	 * Signature: (J)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1show_1background(JNIEnv*, jclass, jlong);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_hide_background
	 * Signature: (J)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1hide_1background(JNIEnv*, jclass, jlong);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_set_font
	 * Signature: (J[BF)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1font(JNIEnv*, jclass, jlong, jbyteArray, jfloat);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_set_weight
	 * Signature: (JI)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1weight(JNIEnv*, jclass, jlong, jint);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_set_style
	 * Signature: (JI)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1style(JNIEnv*, jclass, jlong, jint);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_set_alignment
	 * Signature: (JI)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1alignment(JNIEnv*, jclass, jlong, jint);

	/*
	 * Class:     net_windower_helper_Native
	 * Method:    windower_text_set_padding
	 * Signature: (JF)I
	 */
	JNIEXPORT jint JNICALL Java_net_windower_helper_Native_windower_1text_1set_1padding(JNIEnv*, jclass, jlong, jfloat);
#ifdef __cplusplus
}
#endif

#endif
