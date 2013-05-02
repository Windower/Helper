package net.windower.helper;

public enum KeyState {
	UP(0),
	DOWN(1);

	private int value;

	private KeyState(final int value) {
		this.value = value;
	}

	int intValue() {
		return this.value;
	}
}
