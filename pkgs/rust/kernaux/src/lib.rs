mod ntoa;

pub use ntoa::*;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_ntoa() {
        assert_eq!(utoa8(0o123), "0o123");
        assert_eq!(itoa8(0o123), "0o123");
        assert_eq!(utoa10(123), "123");
        assert_eq!(itoa10(123), "123");
        assert_eq!(utoa16(0x123), "0x123");
        assert_eq!(itoa16(0x123), "0x123");
    }
}
