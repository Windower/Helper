package net.windower.helper;

public enum FontStyle {
	NONE(0),
	ITALIC(1);

	private int value;

	private FontStyle(final int value) {
		this.value = value;
	}

	int intValue() {
		return this.value;
	}
}
