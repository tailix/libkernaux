# frozen_string_literal: true

if ENV['SKIP_COVERAGE'].to_s.empty?
  SimpleCov.start do
    minimum_coverage 95

    add_filter '/spec/'
  end
end
