package net.windower.helper;

import java.util.MissingResourceException;
import java.util.ResourceBundle;

final class WindowerHelperConstants {
	private static final String BUNDLE_NAME = "net.windower.helper.messages"; //$NON-NLS-1$
	private static final ResourceBundle RESOURCE_BUNDLE = ResourceBundle.getBundle(WindowerHelperConstants.BUNDLE_NAME);

	private WindowerHelperConstants() {}

	public static String getString(final String key) {
		try {
			return WindowerHelperConstants.RESOURCE_BUNDLE.getString(key);
		} catch (final MissingResourceException e) {
			return '!' + key + '!';
		}
	}
}
