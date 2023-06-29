import i18n from '@ohos.i18n';

export default class Language {

    private static instance = new Language();

    static getInstance() : Language {
        return Language.instance;
    }

    getSystemLanguage() : string {

        return i18n.getSystemLanguage();
    }
}

globalThis.languageUtils = {};
globalThis.languageUtils.getSystemLanguage=Language.getInstance().getSystemLanguage;