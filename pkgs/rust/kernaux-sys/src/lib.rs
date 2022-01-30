#[cfg(test)]
use libc::{c_char, c_int};

#[cfg(test)]
#[link(name = "kernaux")]
extern "C" {
    fn kernaux_utoa(
        value: u64,
        buffer: *mut c_char,
        base: c_int,
    ) -> *mut c_char;
    fn kernaux_itoa(
        value: i64,
        buffer: *mut c_char,
        base: c_int,
    ) -> *mut c_char;
    fn kernaux_utoa10(value: u64, buffer: *mut c_char);
    fn kernaux_itoa10(value: i64, buffer: *mut c_char);
    fn kernaux_utoa16(value: u64, buffer: *mut c_char);
    fn kernaux_itoa16(value: i64, buffer: *mut c_char);
}

#[cfg(test)]
mod tests {
    use super::*;

    use std::ffi::CStr;

    #[test]
    fn utoa() {
        let mut buffer: [i8; 1000] = [0; 1000];
        let end: *mut c_char =
            unsafe { kernaux_utoa(0x123, buffer.as_mut_ptr(), 'x' as c_int) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(3) });
    }

    #[test]
    fn itoa() {
        let mut buffer: [i8; 1000] = [0; 1000];
        let end: *mut c_char =
            unsafe { kernaux_itoa(0x123, buffer.as_mut_ptr(), 'x' as c_int) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(3) });

        let mut buffer: [i8; 1000] = [0; 1000];
        let end: *mut c_char =
            unsafe { kernaux_itoa(-0x123, buffer.as_mut_ptr(), 'x' as c_int) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "-123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(4) });
    }

    #[test]
    fn utoa10() {
        let mut buffer: [i8; 1000] = [0; 1000];
        unsafe { kernaux_utoa10(123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
    }

    #[test]
    fn itoa10() {
        let mut buffer: [i8; 1000] = [0; 1000];
        unsafe { kernaux_itoa10(123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");

        let mut buffer: [i8; 1000] = [0; 1000];
        unsafe { kernaux_itoa10(-123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "-123");
    }

    #[test]
    fn utoa16() {
        let mut buffer: [i8; 1000] = [0; 1000];
        unsafe { kernaux_utoa16(0x123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
    }

    #[test]
    fn itoa16() {
        let mut buffer: [i8; 1000] = [0; 1000];
        unsafe { kernaux_itoa16(0x123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");

        let mut buffer: [i8; 1000] = [0; 1000];
        unsafe { kernaux_itoa16(-0x123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "-123");
    }
}
