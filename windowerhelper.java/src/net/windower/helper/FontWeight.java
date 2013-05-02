package net.windower.helper;

import java.io.Serializable;

public final class FontWeight implements Serializable {
	private static final long serialVersionUID = -1234695923373134349L;
	
	public static final FontWeight DEFAULT = new FontWeight();
	public static final FontWeight NORMAL = new FontWeight(400);
	public static final FontWeight BOLD = new FontWeight(700);

	private int value;

	private FontWeight() {}

	public FontWeight(final int value) {
		if (value < 1 || value > 999) {
			throw new IllegalArgumentException(String.format(WindowerHelperConstants.getString("argument.range"), "value", 1, 999)); //$NON-NLS-1$ //$NON-NLS-2$
		}

		this.value = value;
	}

	int intValue() {
		return this.value;
	}
}
