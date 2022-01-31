#[cfg(test)]
mod tests {
    use std::ffi::CStr;

    use kernaux_sys::{utoa10, UTOA10_BUFFER_SIZE};

    #[test]
    fn test_utoa10() {
        let mut buffer: [i8; UTOA10_BUFFER_SIZE] = [0; UTOA10_BUFFER_SIZE];
        unsafe { utoa10(123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
    }
}
