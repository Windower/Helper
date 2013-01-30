package net.windower.helper;

public final class Version implements Comparable<Version> {
	private final int version;

	public Version(final int major, final int minor) {
		if (major < 0) {
			throw new IllegalArgumentException(WindowerHelperConstants.getString("version.major_negative")); //$NON-NLS-1$
		} else if (major >= 2147483) {
			throw new IllegalArgumentException(WindowerHelperConstants.getString("version.major_too_big")); //$NON-NLS-1$
		}

		if (minor < 0) {
			throw new IllegalArgumentException(WindowerHelperConstants.getString("version.minor_negative")); //$NON-NLS-1$
		} else if (minor >= 1000) {
			throw new IllegalArgumentException(WindowerHelperConstants.getString("version.minor_too_big")); //$NON-NLS-1$
		}

		this.version = major * 1000 + minor;
	}

	Version(final int version) {
		this.version = version;
	}

	public int compareTo(final Version o) {
		return this.version - o.version;
	}

	public int getMajorVersion() {
		return this.version / 1000;
	}

	public int getMinorVersion() {
		return this.version % 1000;
	}

	@Override
	public String toString() {
		return String.format("%d.%d", this.version / 1000, this.version % 1000); //$NON-NLS-1$
	}
}
