package net.windower.helper;

public enum TextAlignment {
	LEFT(0),
	RIGHT(1);

	private int value;

	private TextAlignment(final int value) {
		this.value = value;
	}

	int intValue() {
		return this.value;
	}
}
