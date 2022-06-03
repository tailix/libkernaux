use kernaux_sys::ntoa::{
    itoa as kernaux_itoa, itoa10 as kernaux_itoa10, itoa16 as kernaux_itoa16,
    itoa2 as kernaux_itoa2, itoa8 as kernaux_itoa8, utoa as kernaux_utoa,
    utoa10 as kernaux_utoa10, utoa16 as kernaux_utoa16, utoa2 as kernaux_utoa2,
    utoa8 as kernaux_utoa8, ITOA10_BUFFER_SIZE, ITOA16_BUFFER_SIZE,
    ITOA2_BUFFER_SIZE, ITOA8_BUFFER_SIZE, ITOA_MIN_BUFFER_SIZE, MAX_PREFIX_LEN,
    UTOA10_BUFFER_SIZE, UTOA16_BUFFER_SIZE, UTOA2_BUFFER_SIZE,
    UTOA8_BUFFER_SIZE, UTOA_MIN_BUFFER_SIZE,
};

use std::ffi::{CStr, CString, NulError};
use std::ptr::null;
use std::str::Utf8Error;

use libc::c_int;

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
pub struct Config {
    base: u8,
    uppercase: bool,
}

pub type Result = std::result::Result<String, Error>;

#[derive(Clone, Debug, Eq, PartialEq)]
pub enum Error {
    PrefixTooLong(usize),
    PrefixIncludesNull(NulError),
    Utf8(Utf8Error),
}

pub fn utoa(value: u64, config: Config, prefix: Option<&str>) -> Result {
    let prefix = if let Some(prefix) = prefix {
        if prefix.len() > MAX_PREFIX_LEN {
            return Err(Error::PrefixTooLong(prefix.len()));
        }
        Some(CString::new(prefix)?)
    } else {
        None
    };

    utoac(value, config, prefix)
}

pub fn itoa(value: i64, config: Config, prefix: Option<&str>) -> Result {
    let prefix = if let Some(prefix) = prefix {
        if prefix.len() > MAX_PREFIX_LEN {
            return Err(Error::PrefixTooLong(prefix.len()));
        }
        Some(CString::new(prefix)?)
    } else {
        None
    };

    itoac(value, config, prefix)
}

fn utoac(value: u64, config: Config, prefix: Option<CString>) -> Result {
    let mut buffer: [i8; UTOA_MIN_BUFFER_SIZE + MAX_PREFIX_LEN] =
        [0; UTOA_MIN_BUFFER_SIZE + MAX_PREFIX_LEN];

    unsafe {
        kernaux_utoa(
            value,
            buffer.as_mut_ptr(),
            config.to_c_int(),
            prefix
                .as_ref()
                .map(|prefix| prefix.as_ptr())
                .unwrap_or(null()),
        );
    };

    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str()?;
    Ok(String::from(result))
}

fn itoac(value: i64, config: Config, prefix: Option<CString>) -> Result {
    let mut buffer: [i8; ITOA_MIN_BUFFER_SIZE + MAX_PREFIX_LEN] =
        [0; ITOA_MIN_BUFFER_SIZE + MAX_PREFIX_LEN];

    unsafe {
        kernaux_itoa(
            value,
            buffer.as_mut_ptr(),
            config.to_c_int(),
            prefix
                .as_ref()
                .map(|prefix| prefix.as_ptr())
                .unwrap_or(null()),
        );
    };

    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str()?;
    Ok(String::from(result))
}

pub fn utoa2(value: u64) -> String {
    let mut buffer: [i8; UTOA2_BUFFER_SIZE] = [0; UTOA2_BUFFER_SIZE];
    unsafe { kernaux_utoa2(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn itoa2(value: i64) -> String {
    let mut buffer: [i8; ITOA2_BUFFER_SIZE] = [0; ITOA2_BUFFER_SIZE];
    unsafe { kernaux_itoa2(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn utoa8(value: u64) -> String {
    let mut buffer: [i8; UTOA8_BUFFER_SIZE] = [0; UTOA8_BUFFER_SIZE];
    unsafe { kernaux_utoa8(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn itoa8(value: i64) -> String {
    let mut buffer: [i8; ITOA8_BUFFER_SIZE] = [0; ITOA8_BUFFER_SIZE];
    unsafe { kernaux_itoa8(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn utoa10(value: u64) -> String {
    let mut buffer: [i8; UTOA10_BUFFER_SIZE] = [0; UTOA10_BUFFER_SIZE];
    unsafe { kernaux_utoa10(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn itoa10(value: i64) -> String {
    let mut buffer: [i8; ITOA10_BUFFER_SIZE] = [0; ITOA10_BUFFER_SIZE];
    unsafe { kernaux_itoa10(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn utoa16(value: u64) -> String {
    let mut buffer: [i8; UTOA16_BUFFER_SIZE] = [0; UTOA16_BUFFER_SIZE];
    unsafe { kernaux_utoa16(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn itoa16(value: i64) -> String {
    let mut buffer: [i8; ITOA16_BUFFER_SIZE] = [0; ITOA16_BUFFER_SIZE];
    unsafe { kernaux_itoa16(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

impl Default for Config {
    fn default() -> Self {
        Self {
            base: 10,
            uppercase: false,
        }
    }
}

impl Config {
    pub fn base(&self) -> u8 {
        self.base
    }

    pub fn uppercase(&self) -> bool {
        self.uppercase
    }

    fn to_c_int(self) -> c_int {
        if self.uppercase {
            (-(self.base as i8)).into()
        } else {
            self.base.into()
        }
    }
}

impl From<NulError> for Error {
    fn from(nul_error: NulError) -> Self {
        Self::PrefixIncludesNull(nul_error)
    }
}

impl From<Utf8Error> for Error {
    fn from(utf8_error: Utf8Error) -> Self {
        Self::Utf8(utf8_error)
    }
}

impl TryFrom<char> for Config {
    type Error = ();

    fn try_from(value: char) -> std::result::Result<Self, Self::Error> {
        let base: i64 = match value {
            'b' | 'B' => 2,
            'o' | 'O' => 8,
            'd' | 'D' => 10,
            'h' | 'x' => 16,
            'H' | 'X' => -16,
            _ => return Err(()),
        };

        base.try_into()
    }
}

impl TryFrom<u64> for Config {
    type Error = ();

    fn try_from(value: u64) -> std::result::Result<Self, Self::Error> {
        if (2..=36).contains(&value) {
            Ok(Self {
                base: value as u8,
                uppercase: false,
            })
        } else {
            Err(())
        }
    }
}

impl TryFrom<i64> for Config {
    type Error = ();

    fn try_from(value: i64) -> std::result::Result<Self, Self::Error> {
        let uppercase = value < 0;
        let value = if value < 0 { -value } else { value };

        if (2..=36).contains(&value) {
            Ok(Self {
                base: value as u8,
                uppercase,
            })
        } else {
            Err(())
        }
    }
}

impl TryFrom<u32> for Config {
    type Error = ();

    fn try_from(value: u32) -> std::result::Result<Self, Self::Error> {
        Self::try_from(value as u64)
    }
}

impl TryFrom<i32> for Config {
    type Error = ();

    fn try_from(value: i32) -> std::result::Result<Self, Self::Error> {
        Self::try_from(value as i64)
    }
}

impl TryFrom<u16> for Config {
    type Error = ();

    fn try_from(value: u16) -> std::result::Result<Self, Self::Error> {
        Self::try_from(value as u64)
    }
}

impl TryFrom<i16> for Config {
    type Error = ();

    fn try_from(value: i16) -> std::result::Result<Self, Self::Error> {
        Self::try_from(value as i64)
    }
}

impl TryFrom<u8> for Config {
    type Error = ();

    fn try_from(value: u8) -> std::result::Result<Self, Self::Error> {
        Self::try_from(value as u64)
    }
}

impl TryFrom<i8> for Config {
    type Error = ();

    fn try_from(value: i8) -> std::result::Result<Self, Self::Error> {
        Self::try_from(value as i64)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_utoa_prefix() {
        assert_eq!(
            utoa(123, Default::default(), Some("foo")),
            Ok("foo123".into()),
        );
        assert_eq!(
            utoa(
                123,
                Default::default(),
                Some("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"),
            ),
            Ok("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa123".into()),
        );
        assert_eq!(
            utoa(
                123,
                Default::default(),
                Some("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"),
            ),
            Err(Error::PrefixTooLong(101)),
        );
    }

    #[test]
    fn test_itoa_prefix() {
        assert_eq!(
            itoa(123, Default::default(), Some("foo")),
            Ok("foo123".into()),
        );
        assert_eq!(
            itoa(-123, Default::default(), Some("foo")),
            Ok("-foo123".into()),
        );
        assert_eq!(
            itoa(
                123,
                Default::default(),
                Some("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"),
            ),
            Ok("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa123".into()),
        );
        assert_eq!(
            itoa(
                123,
                Default::default(),
                Some("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"),
            ),
            Err(Error::PrefixTooLong(101)),
        );
    }

    #[test]
    fn test_utoa() {
        // binary
        assert_eq!(
            utoa(0b10110, 'b'.try_into().unwrap(), None),
            Ok("10110".into()),
        );
        assert_eq!(
            utoa(0b10110, 'B'.try_into().unwrap(), None),
            Ok("10110".into()),
        );
        assert_eq!(
            utoa(0b10110, 2.try_into().unwrap(), None),
            Ok("10110".into()),
        );
        assert_eq!(
            utoa(0b10110, (-2).try_into().unwrap(), None),
            Ok("10110".into()),
        );

        // octal
        assert_eq!(
            utoa(0o123, 'o'.try_into().unwrap(), None),
            Ok("123".into()),
        );
        assert_eq!(
            utoa(0o123, 'O'.try_into().unwrap(), None),
            Ok("123".into()),
        );
        assert_eq!(utoa(0o123, 8.try_into().unwrap(), None), Ok("123".into()));
        assert_eq!(
            utoa(0o123, (-8).try_into().unwrap(), None),
            Ok("123".into()),
        );

        // decimal
        assert_eq!(utoa(123, Default::default(), None), Ok("123".into()));
        assert_eq!(utoa(123, 'd'.try_into().unwrap(), None), Ok("123".into()));
        assert_eq!(utoa(123, 'D'.try_into().unwrap(), None), Ok("123".into()));
        assert_eq!(utoa(123, 10.try_into().unwrap(), None), Ok("123".into()));
        assert_eq!(
            utoa(123, (-10).try_into().unwrap(), None),
            Ok("123".into()),
        );

        // hexadecimal
        assert_eq!(
            utoa(0x123cafe, 'x'.try_into().unwrap(), None),
            Ok("123cafe".into()),
        );
        assert_eq!(
            utoa(0x123cafe, 16.try_into().unwrap(), None),
            Ok("123cafe".into()),
        );
        assert_eq!(
            utoa(0x123cafe, 'X'.try_into().unwrap(), None),
            Ok("123CAFE".into()),
        );
        assert_eq!(
            utoa(0x123cafe, (-16).try_into().unwrap(), None),
            Ok("123CAFE".into()),
        );

        // random base: 14
        assert_eq!(
            utoa(123456, 14.try_into().unwrap(), None),
            Ok("32dc4".into()),
        );
        assert_eq!(
            utoa(123456, (-14).try_into().unwrap(), None),
            Ok("32DC4".into()),
        );
    }

    #[test]
    fn test_itoa() {
        // binary
        assert_eq!(
            itoa(0b10110, 'b'.try_into().unwrap(), None),
            Ok("10110".into()),
        );
        assert_eq!(
            itoa(-0b10110, 'B'.try_into().unwrap(), None),
            Ok("-10110".into()),
        );
        assert_eq!(
            itoa(-0b10110, 2.try_into().unwrap(), None),
            Ok("-10110".into()),
        );
        assert_eq!(
            itoa(0b10110, (-2).try_into().unwrap(), None),
            Ok("10110".into()),
        );

        // octal
        assert_eq!(
            itoa(-0o123, 'o'.try_into().unwrap(), None),
            Ok("-123".into()),
        );
        assert_eq!(
            itoa(0o123, 'O'.try_into().unwrap(), None),
            Ok("123".into()),
        );
        assert_eq!(itoa(0o123, 8.try_into().unwrap(), None), Ok("123".into()));
        assert_eq!(
            itoa(-0o123, (-8).try_into().unwrap(), None),
            Ok("-123".into()),
        );

        // decimal
        assert_eq!(itoa(123, Default::default(), None), Ok("123".into()));
        assert_eq!(
            itoa(-123, 'd'.try_into().unwrap(), None),
            Ok("-123".into()),
        );
        assert_eq!(
            itoa(-123, 'D'.try_into().unwrap(), None),
            Ok("-123".into()),
        );
        assert_eq!(itoa(123, 10.try_into().unwrap(), None), Ok("123".into()));
        assert_eq!(
            itoa(123, (-10).try_into().unwrap(), None),
            Ok("123".into()),
        );

        // hexadecimal
        assert_eq!(
            itoa(-0x123cafe, 'x'.try_into().unwrap(), None),
            Ok("-123cafe".into()),
        );
        assert_eq!(
            itoa(0x123cafe, 16.try_into().unwrap(), None),
            Ok("123cafe".into()),
        );
        assert_eq!(
            itoa(0x123cafe, 'X'.try_into().unwrap(), None),
            Ok("123CAFE".into()),
        );
        assert_eq!(
            itoa(-0x123cafe, (-16).try_into().unwrap(), None),
            Ok("-123CAFE".into()),
        );

        // random base: 14
        assert_eq!(
            itoa(123456, 14.try_into().unwrap(), None),
            Ok("32dc4".into()),
        );
        assert_eq!(
            itoa(-123456, (-14).try_into().unwrap(), None),
            Ok("-32DC4".into()),
        );
        assert_eq!(
            itoa(-123456, 14.try_into().unwrap(), None),
            Ok("-32dc4".into()),
        );
        assert_eq!(
            itoa(123456, (-14).try_into().unwrap(), None),
            Ok("32DC4".into()),
        );
    }

    #[test]
    fn test_utoa2() {
        assert_eq!(utoa2(0), "0b0");
        assert_eq!(utoa2(1), "0b1");
        assert_eq!(utoa2(123), "0b1111011");
        assert_eq!(
            utoa2(u64::MAX),
            "0b1111111111111111111111111111111111111111111111111111111111111111",
        );
    }

    #[test]
    fn test_itoa2() {
        assert_eq!(itoa2(0), "0b0");
        assert_eq!(itoa2(1), "0b1");
        assert_eq!(itoa2(-1), "-0b1");
        assert_eq!(itoa2(123), "0b1111011");
        assert_eq!(itoa2(-123), "-0b1111011");
        assert_eq!(
            itoa2(i64::MAX),
            "0b111111111111111111111111111111111111111111111111111111111111111",
        );
        assert_eq!(
            itoa2(i64::MIN),
            "-0b1000000000000000000000000000000000000000000000000000000000000000",
        );
    }

    #[test]
    fn test_utoa8() {
        assert_eq!(utoa8(0), "0o0");
        assert_eq!(utoa8(1), "0o1");
        assert_eq!(utoa8(0o123), "0o123");
        assert_eq!(utoa8(u64::MAX), "0o1777777777777777777777");
    }

    #[test]
    fn test_itoa8() {
        assert_eq!(itoa8(0), "0o0");
        assert_eq!(itoa8(1), "0o1");
        assert_eq!(itoa8(-1), "-0o1");
        assert_eq!(itoa8(0o123), "0o123");
        assert_eq!(itoa8(-0o123), "-0o123");
        assert_eq!(itoa8(i64::MAX), "0o777777777777777777777");
        assert_eq!(itoa8(i64::MIN), "-0o1000000000000000000000");
    }

    #[test]
    fn test_utoa10() {
        assert_eq!(utoa10(0), "0");
        assert_eq!(utoa10(1), "1");
        assert_eq!(utoa10(123), "123");
        assert_eq!(utoa10(u64::MAX), "18446744073709551615");
    }

    #[test]
    fn test_itoa10() {
        assert_eq!(itoa10(0), "0");
        assert_eq!(itoa10(1), "1");
        assert_eq!(itoa10(-1), "-1");
        assert_eq!(itoa10(123), "123");
        assert_eq!(itoa10(-123), "-123");
        assert_eq!(itoa10(i64::MAX), "9223372036854775807");
        assert_eq!(itoa10(i64::MIN), "-9223372036854775808");
    }

    #[test]
    fn test_utoa16() {
        assert_eq!(utoa16(0), "0x0");
        assert_eq!(utoa16(1), "0x1");
        assert_eq!(utoa16(0x123), "0x123");
        assert_eq!(utoa16(u64::MAX), "0xffffffffffffffff");
    }

    #[test]
    fn test_itoa16() {
        assert_eq!(itoa16(0), "0x0");
        assert_eq!(itoa16(1), "0x1");
        assert_eq!(itoa16(-1), "-0x1");
        assert_eq!(itoa16(0x123), "0x123");
        assert_eq!(itoa16(-0x123), "-0x123");
        assert_eq!(itoa16(i64::MAX), "0x7fffffffffffffff");
        assert_eq!(itoa16(i64::MIN), "-0x8000000000000000");
    }

    #[test]
    fn test_config_default() {
        assert_eq!(
            Config::default(),
            Config {
                base: 10,
                uppercase: false,
            },
        );
    }

    #[test]
    fn test_try_config_from_unsigned() {
        assert_eq!(Config::try_from(12u8), Config::try_from(12u64));
        assert_eq!(Config::try_from(12i8), Config::try_from(12i64));
        assert_eq!(Config::try_from(12u16), Config::try_from(12u64));
        assert_eq!(Config::try_from(12i16), Config::try_from(12i64));
        assert_eq!(Config::try_from(12u32), Config::try_from(12u64));
        assert_eq!(Config::try_from(12i32), Config::try_from(12i64));
    }

    #[test]
    fn test_try_config_from_u64() {
        assert_eq!(Config::try_from(0u64), Err(()));
        assert_eq!(Config::try_from(1u64), Err(()));
        assert_eq!(Config::try_from(37u64), Err(()));
        assert_eq!(
            Config::try_from(2u64),
            Ok(Config {
                base: 2,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from(10u64),
            Ok(Config {
                base: 10,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from(36u64),
            Ok(Config {
                base: 36,
                uppercase: false,
            }),
        );
    }

    #[test]
    fn test_try_config_from_i64() {
        assert_eq!(Config::try_from(0i64), Err(()));
        assert_eq!(Config::try_from(1i64), Err(()));
        assert_eq!(Config::try_from(-1i64), Err(()));
        assert_eq!(Config::try_from(37i64), Err(()));
        assert_eq!(Config::try_from(-37i64), Err(()));
        assert_eq!(
            Config::try_from(2i64),
            Ok(Config {
                base: 2,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from(-2i64),
            Ok(Config {
                base: 2,
                uppercase: true,
            }),
        );
        assert_eq!(
            Config::try_from(10i64),
            Ok(Config {
                base: 10,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from(-10i64),
            Ok(Config {
                base: 10,
                uppercase: true,
            }),
        );
        assert_eq!(
            Config::try_from(36i64),
            Ok(Config {
                base: 36,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from(-36i64),
            Ok(Config {
                base: 36,
                uppercase: true,
            }),
        );
    }

    #[test]
    fn test_try_config_from_char() {
        assert_eq!(Config::try_from('a'), Err(()));
        assert_eq!(Config::try_from('A'), Err(()));
        assert_eq!(Config::try_from('z'), Err(()));
        assert_eq!(Config::try_from('Z'), Err(()));
        assert_eq!(
            Config::try_from('b'),
            Ok(Config {
                base: 2,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from('B'),
            Ok(Config {
                base: 2,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from('o'),
            Ok(Config {
                base: 8,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from('O'),
            Ok(Config {
                base: 8,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from('d'),
            Ok(Config {
                base: 10,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from('D'),
            Ok(Config {
                base: 10,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from('h'),
            Ok(Config {
                base: 16,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from('H'),
            Ok(Config {
                base: 16,
                uppercase: true,
            }),
        );
        assert_eq!(
            Config::try_from('x'),
            Ok(Config {
                base: 16,
                uppercase: false,
            }),
        );
        assert_eq!(
            Config::try_from('X'),
            Ok(Config {
                base: 16,
                uppercase: true,
            }),
        );
    }
}
