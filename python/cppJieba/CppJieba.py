# import jieba_pybind as jp
from jieba_pybind import cppjieba

_DICT_PATH = "./dict/jieba.dict.utf8"
_HMM_PATH = "./dict/hmm_model.utf8"
_USER_DICT_PATH = "./dict/user.dict.utf8"
_IDF_PATH = "./dict/idf.utf8"
_STOP_WORD_PATH = "./dict/stop_words.utf8"

_jp = None

def cut(sentence):
    global _jp
    if _jp == None:
        _jp = cppjieba(_DICT_PATH,_HMM_PATH,_USER_DICT_PATH,_IDF_PATH,_STOP_WORD_PATH)
    return _jp.cut(sentence)

def load_userdict(dict_path):
    global _USER_DICT_PATH
    _USER_DICT_PATH = dict_path

def set_stop_word(stop_word_path):
    global _STOP_WORD_PATH
    _STOP_WORD_PATH = stop_word_path