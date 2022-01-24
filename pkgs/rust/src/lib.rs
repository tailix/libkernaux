#[cfg(test)]
use libc::{c_char, c_int};

#[link(name = "kernaux")]
extern "C" {
    #[cfg(test)]
    fn kernaux_utoa(value: u64, buffer: *mut c_char, base: c_int) -> *mut c_char;
    #[cfg(test)]
    fn kernaux_itoa(value: i64, buffer: *mut c_char, base: c_int) -> *mut c_char;
    #[cfg(test)]
    fn kernaux_utoa10(value: u64, buffer: *mut c_char);
    #[cfg(test)]
    fn kernaux_itoa10(value: i64, buffer: *mut c_char);
    #[cfg(test)]
    fn kernaux_utoa16(value: u64, buffer: *mut c_char);
    #[cfg(test)]
    fn kernaux_itoa16(value: i64, buffer: *mut c_char);
}

#[cfg(test)]
mod tests {
    use super::*;

    use std::ffi::CStr;

    #[test]
    fn utoa() {
        let mut buffer: [i8; 1000] = [0; 1000];
        unsafe { kernaux_utoa(0x123, buffer.as_mut_ptr(), 'x' as c_int) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
    }

    #[test]
    fn itoa() {
        let mut buffer: [i8; 1000] = [0; 1000];
        unsafe { kernaux_itoa(0x123, buffer.as_mut_ptr(), 'x' as c_int) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
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
