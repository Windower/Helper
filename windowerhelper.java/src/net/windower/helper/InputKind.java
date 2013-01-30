package net.windower.helper;

import java.util.EnumSet;

public enum InputKind {
	NONE(0),
	KEYBOARD(1),
	MOUSE(2);

	public static EnumSet<InputKind> all() {
		return EnumSet.of(KEYBOARD, MOUSE);
	}

	private int value;

	private InputKind(final int value) {
		this.value = value;
	}

	int intValue() {
		return this.value;
	}
}
