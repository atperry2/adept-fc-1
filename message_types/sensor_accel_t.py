"""ZCM type definitions
This file automatically generated by zcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class sensor_accel_t(object):
    __slots__ = ["a_x", "a_y", "a_z", "t"]

    def __init__(self):
        self.a_x = 0.0
        self.a_y = 0.0
        self.a_z = 0.0
        self.t = 0.0

    def encode(self):
        buf = BytesIO()
        buf.write(sensor_accel_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">dddd", self.a_x, self.a_y, self.a_z, self.t))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != sensor_accel_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return sensor_accel_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = sensor_accel_t()
        self.a_x, self.a_y, self.a_z, self.t = struct.unpack(">dddd", buf.read(32))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if sensor_accel_t in parents: return 0
        tmphash = (0x2d589603ac8e0da0) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff)  + ((tmphash>>63)&0x1)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if sensor_accel_t._packed_fingerprint is None:
            sensor_accel_t._packed_fingerprint = struct.pack(">Q", sensor_accel_t._get_hash_recursive([]))
        return sensor_accel_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

