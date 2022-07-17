#!/usr/bin/python
import unittest

from subprocess import PIPE, Popen


CODE_SCRIPT = "cat ip_filter/static/ip_filter.tsv | " \
              "./build/bin/ip_filter | " \
              "md5sum"


class MyTestCase(unittest.TestCase):
    def test_hash_result(self):
        with Popen(CODE_SCRIPT, shell=True, stdout=PIPE) as process:
            result = process.stdout
            result_hash = result.read().decode().rstrip()

        expected_hash = "24e7a7b2270daee89c64d3ca5fb3da1a  -"
        self.assertEqual(expected_hash, result_hash, "failed compare hash")


if __name__ == '__main__':
    unittest.main()
